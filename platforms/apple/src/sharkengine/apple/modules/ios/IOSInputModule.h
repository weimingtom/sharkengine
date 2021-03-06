//
//  IOSInputModule.h
//  SharkEngine
//
//  Created by Jon Sharkey on 2013-11-13.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef SHARKENGINE_APPLE_MODULES_IOS_IOSINPUTMODULE_H_
#define SHARKENGINE_APPLE_MODULES_IOS_IOSINPUTMODULE_H_

#include "sharkengine/animation.h"
#include "sharkengine/modules/input_module.h"

@class OrientationListener;

class IOSInputModule : public InputModule {
 public:
  IOSInputModule();
  ~IOSInputModule();

  void SetTargetDeviceAngle(float target_device_angle);

  // InputModule
  void TurnOnRotationUpdates();
  void TurnOffRotationUpdates();
  float device_angle() { return device_angle_; }

  // Simulator
  virtual void SimulateStep();

 private:
  float device_angle_;
  Animation device_angle_animation_;
  OrientationListener *orientation_listener_;
};

#endif
