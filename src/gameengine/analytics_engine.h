//
//  analytics_engine.h
//  GameEngine
//
//  Created by Jon Sharkey on 2013-03-05.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_ANALYITICSENGINE_H_
#define GAMEENGINE_ANALYITICSENGINE_H_

struct ScreenPoint;

class AnalyticsEngine {
 public:
  virtual void LogEvent(std::string event_name) = 0;
  virtual void LogEvent(std::string event_name, std::map<std::string, std::string> parameters) = 0;
};

#endif
