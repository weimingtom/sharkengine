//
//  game_engine.cc
//  GameEngine
//
//  Created by Jon Sharkey on 2010-04-10.
//  Copyright 2010 Sharkable. All rights reserved.
//

#include "gameengine/game_engine.h"

#include "gameengine/engine_view.h"

#include "gameengine/modules/ad_engine.h"
#include "gameengine/modules/analytics_engine.h"
#include "gameengine/modules/app_store_engine.h"
#include "gameengine/modules/input_module.h"
#include "gameengine/modules/local_store.h"
#include "gameengine/modules/module_factory.h"

GameEngine::GameEngine(sp<ModuleFactory> module_factory)
    : module_factory_(module_factory),
      platform_type_(kPlatformTypePhone),
      resource_loader_(*this),
      mouse_delta_x_(0),
      mouse_delta_y_(0),
      screen_size_(kScreenSizeZero),
      screen_offset_(kScreenPointZero),
      screen_to_game_point_ratio_x_(1),
      screen_to_game_point_ratio_y_(1) {
  local_store_.reset(new LocalStore());
  ad_module_.reset(new AdModule());
  analytics_engine_.reset(new AnalyticsEngine());
  app_store_engine_.reset(new AppStoreEngine());
  input_module_.reset(new InputModule());

  positions_ = sp<Positions>(new Positions());
}

void GameEngine::Update() {
  if (next_views_.size() > 0) {
    sp<EngineView> back;
    if (views_.size()) {
      back = views_.back();
      back->ClearTouches();
    }
    views_ = next_views_;
    // If the back view has changed, then call focus notificaitons.
    if (views_.back() != back) {
      if (back) {
        back->ViewDidLoseFocus();
      }
      views_.back()->ViewDidGainFocus();
    }
    next_views_.clear();
  }

  assert(views_.size() > 0);

  // Process input.
  sp<EngineView> touch_view;
  for (auto i = views_.rbegin(); i != views_.rend(); i++) {
    if ((*i)->IsCapturingTouches()) {
      touch_view = *i;
      break;
    }
  }
  if (touch_view) {
    if (touches_began_.size() > 0) {
      touch_view->TouchesBegan(touches_began_);
      touches_began_.clear();
    }
    if (touches_moved_.size() > 0) {
      touch_view->TouchesMoved(touches_moved_);
      touches_moved_.clear();
    }
    if (touches_ended_.size() > 0) {
      touch_view->TouchesEnded(touches_ended_);
      touches_ended_.clear();
    }
    // TODO should this be called if both values are 0?
    touch_view->HandleMouseDelta(mouse_delta_x_, mouse_delta_y_);
    mouse_delta_x_ = 0;
    mouse_delta_y_ = 0;
  }

  // Update views.
  for (int i = 0; i < views_.size(); i++) {
    views_[i]->Update();
  }
}

void GameEngine::Render() {
  for (int i = 0; i < views_.size(); i++) {
    views_[i]->Render();
  }
}

void GameEngine::NotifyPause() {
  for (int i = 0; i < views_.size(); i++) {
    views_[i]->NotifyPause();
  }
}

void GameEngine::ClearTouches() {
  for (int i = 0; i < views_.size(); i++) {
    views_[i]->ClearTouches();
  }
}

void GameEngine::AddTouchBegan(Touch touch) {
  touches_began_.push_back(touch);
}

void GameEngine::AddTouchMoved(Touch touch) {
  touches_moved_.push_back(touch);
}

void GameEngine::AddTouchEnded(Touch touch) {
  touches_ended_.push_back(touch);
}

void GameEngine::AddMouseDelta(float delta_x, float delta_y) {
  mouse_delta_x_ += delta_x;
  mouse_delta_y_ += delta_y;
}

bool GameEngine::HandleBackButton() {
  if (views_.size() == 0) {
    return false;
  }
  return views_.back()->HandleBackButton();
}

void GameEngine::HandlePauseButton() {
  if (views_.size() != 0) {
    views_.back()->HandlePauseButton();
  }
}

void GameEngine::PushView(sp<EngineView> view) {
  if (next_views_.size() == 0) {
    next_views_ = views_;
  }
  next_views_.push_back(view);
}

void GameEngine::PopView() {
  assert(views_.size() > 0);
  if (next_views_.size() == 0) {
    next_views_ = views_;
  }
  next_views_.pop_back();
}

void GameEngine::RemoveView(EngineView *view) {
  if (next_views_.size() == 0) {
    next_views_ = views_;
  }
  for (auto i = next_views_.begin(); i != next_views_.end(); i++) {
    if (i->get() == view) {
      i = next_views_.erase(i);
      break;
    }
  }
}

void GameEngine::SetRootView(sp<EngineView> view) {
  next_views_.clear();
  next_views_.push_back(view);
}

sp<AssetReader> GameEngine::CreateAssetReader(std::string filename) {
  return module_factory_->CreateAssetReader(filename);
}
