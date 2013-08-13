//
//  IOSIAdAdEngine.h
//  GameEngine
//
//  Created by Jon Sharkey on 2013-08-13.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_APPLE_MODULES_IOS_IOSIADADENGINE_H
#define GAMEENGINE_APPLE_MODULES_IOS_IOSIADADENGINE_H

#include <string>

#include "gameengine/modules/ad_engine.h"

@class IAdInterstitialState;

class IOSIAdAdEngine : public AdEngine {
 public:
  IOSIAdAdEngine(UIViewController *root_view_controller);
  ~IOSIAdAdEngine();

  // AdEngine
  void SetPublisherId(std::string publisher_id);
  void SetAdAtPoint(ScreenPoint point);
  void RemoveAd();
  void PrepareFullScreenAd();
  bool ShowFullScreenAd();
  bool IsShowingFullScreenAd();

  // Module
  bool IsImplemented() { return true; };

 private:
  IAdInterstitialState *interstitial_state_;
  UIViewController *root_view_controller_;
};

#endif