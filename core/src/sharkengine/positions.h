//
//  positions.h
//  SharkEngine
//
//  Created by Jon Sharkey on 2013-02-19.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef SHARKENGINE_POSITIONS_H_
#define SHARKENGINE_POSITIONS_H_

#include "sharkengine/coordinates/coordinate_types.h"

#include <map>
#include <string>

class AssetReader;

class Positions {
 public:
  GamePoint position(std::string name) { return positions_[name]; }
  void LoadFile(AssetReader &asset_reader);

 private:
  std::map<std::string, GamePoint> positions_;
};

#endif
