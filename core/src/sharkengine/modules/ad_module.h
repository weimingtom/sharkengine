//
//  ad_module.h
//  SharkEngine
//
//  Created by Jon Sharkey on 2012-02-25.
//  Copyright 2012 Sharkable. All rights reserved.
//

#ifndef SHARKENGINE_ADMODULE_H_
#define SHARKENGINE_ADMODULE_H_

#include <string>

#include "sharkengine/module.h"
#include "sharkengine/coordinates/coordinate_types.h"

class AdModule : public Module {
 public:
  virtual void SetPublisherId(const std::string & publisher_id) {};
  virtual void SetAdAtPoint(ScreenPoint point) {};
  virtual void RemoveAd() {};
  virtual void PrepareFullScreenAd() {};
  virtual bool ShowFullScreenAd() { return false; };
  virtual bool IsShowingFullScreenAd() { return false; };
};

#endif
