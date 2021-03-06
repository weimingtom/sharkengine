//
//  asset_reader.h
//  SharkEngine
//
//  Created by Jon Sharkey on 2013-04-19.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef SHARKENGINE_ASSETREADER_H_
#define SHARKENGINE_ASSETREADER_H_

class AssetReader {
 public:
  virtual ~AssetReader() {};
  virtual size_t Size() = 0;
  virtual size_t Read(void *ptr, size_t size, size_t count) = 0;
  virtual bool Close() = 0;
  virtual bool IsOpen() = 0;
};

#endif
