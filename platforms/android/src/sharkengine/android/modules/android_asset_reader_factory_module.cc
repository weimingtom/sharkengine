//
//  android_asset_reader_factory_module.cc
//  SharkEngine
//
//  Created by Jon Sharkey on 2013-04-19.
//  Copyright 2013 Sharkable. All rights reserved.
//

#include "sharkengine/android/modules/android_asset_reader_factory_module.h"

#include "sharkengine/android/android_asset_reader.h"

using std::string;

// AssetReaderFactoryModule

AssetReader * AndroidAssetReaderFactoryModule::CreateAssetReader(std::string filename) {
  return new AndroidAssetReader(filename);
}
