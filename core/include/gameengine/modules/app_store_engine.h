//
//  app_store_engine.h
//  GameEngine
//
//  Created by Jon Sharkey on 2013-03-20.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_APPSTOREENGINE_H_
#define GAMEENGINE_APPSTOREENGINE_H_

class AppStoreEngine {
 public:
  virtual void AskForRate() = 0;
  virtual void AskForUpgrade(std::string app_name, std::string app_id) = 0;
};

#endif
