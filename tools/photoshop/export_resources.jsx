var activeDocument = app.activeDocument;
var outputFolder = activeDocument.path + "/textures";
var outputPositionsFolder = activeDocument.path + "/../assets/positions";
var outputPositionsFilename = "positions.xml";
var layerVisibleMap = new Array();
var layerPositionMap = {};
var rulerOffset = getRulerOffset();

var response = prompt("It this for Retina Display? iPhone?", 'nn');
var isRetina = response[0] != 'n' && response[0] != 'N';
var isPhone = response[1] != 'n' && response[1] != 'N';
var useIPadGameSize = false;

var layerIndexes = getLayerSetsIndex();

for (var i = 0; i < layerIndexes.length; i++) {
  var index = layerIndexes[i];
  layerVisibleMap[index] = getLayerVisibilityByIndex(index);
  makeActiveByIndex(index, false);
  activeDocument.activeLayer.visible = false;
}

for (var i = 0; i < layerIndexes.length; i++) {
  makeActiveByIndex(layerIndexes[i], false);
  var layerName = activeDocument.activeLayer.name;
  if (layerName.length >= 2 && (layerName[0] == '_' || layerName[0] == '@')) {
    createResourceFromLayerSet(activeDocument.activeLayer, isRetina);
  }
  if (layerName.length >= 2 && (layerName[0] == '#' || layerName[0] == '^')) {
    if (layerName[0] == '#') {
      useIPadGameSize = true;
    }
    outputPositionsFilename = layerName.substring(1) + (isPhone ? "_iphone" : "") + ".xml";
  }
}

for (var i = 0; i < layerIndexes.length; i++) {
  var index = layerIndexes[i];
  makeActiveByIndex(index, false);
  activeDocument.activeLayer.visible = layerVisibleMap[index];
}

var layerPositionMapIsEmpty = true;
for (var key in layerPositionMap) {
  layerPositionMapIsEmpty = false;
  break;
}
if (!layerPositionMapIsEmpty && ((!isPhone && !isRetina) || (isPhone && isRetina))) {
  var positionsFile = new File(outputPositionsFolder + "/" + outputPositionsFilename);
  positionsFile.open('w');
  positionsFile.writeln('<positions>');
  for (var layerName in layerPositionMap) {
    positionsFile.writeln('  <position name=\"' + layerName + '\">');
    positionsFile.writeln('    <x>' + layerPositionMap[layerName][0].value + '</x>');
    positionsFile.writeln('    <y>' + layerPositionMap[layerName][1].value + '</y>');
    positionsFile.writeln('  </position>');
  }
  positionsFile.writeln('</positions>');
  positionsFile.close();
}

function getRulerOffset() {
   var ref = new ActionReference();
   ref.putEnumerated(charIDToTypeID("Dcmn"), charIDToTypeID("Ordn"), charIDToTypeID("Trgt"));
   var xOffset = executeActionGet(ref).getInteger(stringIDToTypeID('rulerOriginH')) / 65536;
   var yOffset = executeActionGet(ref).getInteger(stringIDToTypeID('rulerOriginV')) / 65536;
   return [xOffset, yOffset];
};

function getLayerSetsIndex() {  
   function getNumberLayers() { 
     var ref = new ActionReference(); 
     ref.putProperty(charIDToTypeID("Prpr"), charIDToTypeID("NmbL")); 
     ref.putEnumerated(charIDToTypeID("Dcmn"), charIDToTypeID("Ordn"), charIDToTypeID("Trgt")); 
     return executeActionGet(ref).getInteger(charIDToTypeID("NmbL")); 
   } 

   function hasBackground() {
     var ref = new ActionReference(); 
     ref.putProperty( charIDToTypeID("Prpr"), charIDToTypeID("Bckg")); 
     // bottom Layer/background 
     ref.putEnumerated(charIDToTypeID("Lyr "), charIDToTypeID("Ordn"), charIDToTypeID("Back")); 
     var desc = executeActionGet(ref);
     var res = desc.getBoolean(charIDToTypeID("Bckg"));
     return res   
    };

   function getLayerType(idx,prop) {        
       var ref = new ActionReference(); 
       ref.putIndex(charIDToTypeID("Lyr "), idx);
       var desc = executeActionGet(ref);
       var type = desc.getEnumerationValue(prop);
       var res = typeIDToStringID(type); 
       return res   
    };

   var cnt = getNumberLayers() + 1; 
   var res = new Array(); 

   if (hasBackground()) { 
     var i = 0; 
   } else{ 
     var i = 1; 
   };

   var prop = stringIDToTypeID("layerSection")  
   for(i; i < cnt; i++){ 
      var temp = getLayerType(i, prop); 
      if (temp == "layerSectionStart") res.push(i); 
   }; 
   return res; 
};

function getLayerVisibilityByIndex(idx) {
  var ref = new ActionReference();
  ref.putProperty(charIDToTypeID("Prpr"), charIDToTypeID("Vsbl"));
  ref.putIndex(charIDToTypeID("Lyr " ), idx);
  return executeActionGet(ref).getBoolean(charIDToTypeID("Vsbl"));;
};

function makeActiveByIndex(idx, visible) {
  var desc = new ActionDescriptor();
  var ref = new ActionReference();
  ref.putIndex(charIDToTypeID("Lyr "), idx);
  desc.putReference(charIDToTypeID("null"), ref);
  desc.putBoolean(charIDToTypeID("MkVs"), visible);
  executeAction(charIDToTypeID("slct"), desc, DialogModes.NO);
};

function pasteInPlace() {
  var idpast = charIDToTypeID("past");
  var desc557 = new ActionDescriptor();
  var idinPlace = stringIDToTypeID("inPlace");
  desc557.putBoolean(idinPlace, true);
  var idAntA = charIDToTypeID("AntA");
  var idAnnt = charIDToTypeID("Annt");
  var idAnno = charIDToTypeID("Anno");
  desc557.putEnumerated(idAntA, idAnnt, idAnno);
  executeAction(idpast, desc557, DialogModes.NO);
}

function recursiveSetLayerSetVisible(layer, visible) {
  layer.visible = visible;
  var layerSets = layer.layerSets;
  if (layerSets) {
    for (var i = 0; i < layerSets.length; i++) {
     recursiveSetLayerSetVisible(layerSets[i], visible);
    }
  }
}

function setParentsVisible(layerSet, visible) {
  var parent = layerSet.parent; 
  while (parent != activeDocument) {
    parent.visible = visible;  
    parent = parent.parent;
  }  
}

function createResourceFromLayerSet(layerSet, isRetina) {
  var name = layerSet.name;
  var saveFile = name[0] == '_' || name[1] == '_';
  var savePosition = name[0] == '@' || name[1] == '@';
  var originalLayerName = layerSet.name.substring(saveFile && savePosition ? 2 : 1);
  var documentName = originalLayerName;
  if (isPhone) {
    documentName += "_iphone";
  }
  if (isRetina) {
    documentName += "@2x";
  }

  recursiveSetLayerSetVisible(layerSet, true);
  setParentsVisible(layerSet, true);

  activeDocument.selection.selectAll();
  activeDocument.selection.copy(true);
 
  recursiveSetLayerSetVisible(layerSet, false);
  setParentsVisible(layerSet, false);

  var document = app.documents.add(activeDocument.width, activeDocument.height, 72, documentName,
                                   NewDocumentMode.RGB, DocumentFill.TRANSPARENT);
  pasteInPlace();

  var oldWidth = document.width;
  var oldHeight = document.height;
  document.trim(TrimType.TRANSPARENT, true, true, false, false);
  var x = oldWidth - document.width - rulerOffset[0];
  var y = oldHeight - document.height - rulerOffset[1];
  document.trim(TrimType.TRANSPARENT, false, false, true, true);

  if (savePosition) {
    // documentName might include a path, but we just want the filename.
    var positionName = originalLayerName.split("/").pop();
    if (isPhone && useIPadGameSize) {
      layerPositionMap[positionName] = [x * (768.0 / 320.0 / 2), y * (768.0 / 320.0 / 2)];
    } else {
      layerPositionMap[positionName] = [x, y];      
    }
  }

  if (saveFile) {
    var pngSaveOptions = new PNGSaveOptions();
    pngSaveOptions.interlaced = false;
    document.saveAs(new File(outputFolder + "/" + documentName), pngSaveOptions, true);
  }

  document.close(SaveOptions.DONOTSAVECHANGES);
}
