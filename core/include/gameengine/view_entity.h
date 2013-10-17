//
//  view_entity.h
//  GameEngine
//
//  Created by Jon Sharkey on 2010-04-10.
//  Copyright 2010 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_VIEWENTITY_H_
#define GAMEENGINE_VIEWENTITY_H_

#include <vector>

#include "gameengine/coordinate_types.h"
#include "gameengine/touch.h"

class EngineView;

class ViewEntity {
 public:
  ViewEntity() : engine_view_(NULL) {}
  virtual ~ViewEntity() {}

  virtual void Update() = 0;
  virtual void Render(GamePoint offset) = 0;
  virtual bool TouchBegan(GamePoint offset, Touch touch) { return false; }
  virtual void TouchMoved(GamePoint offset, Touch touch) {}
  virtual void TouchEnded(GamePoint offset, Touch touch) {}
  virtual void TouchTapped(GamePoint offset, Touch touch) {}
  virtual void ClearTouches() {}
  virtual void KeyPressed(int key) {}
  virtual void HandleMouseDelta(float delta_x, float delta_y) {}

  // Accessors
  virtual EngineView * view() { return engine_view_; }

 private:
  virtual void SetEngineView(EngineView *engine_view) { engine_view_ = engine_view; }
  friend class CompositeEntity;
  friend class EngineView;

  EngineView *engine_view_;  // weak
};

#endif
