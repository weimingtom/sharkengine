//
//  simple_item.cc
//  GameEngine
//
//  Created by Jonathan Sharkey on 10-04-30.
//  Copyright 2010 Sharkable. All rights reserved.
//

#import "gameengine/entities/simple_item.h"

#import "gameengine/resource_loader.h"

SimpleItem::SimpleItem()
    : Animatable(),
      sprite_(0) {
}

SimpleItem::SimpleItem(Sprite sprite, GamePoint position)
    : Animatable(position),
      sprite_(0) {
  sprites_.push_back(sprite);
}

SimpleItem::SimpleItem(vector<Sprite> sprites, GamePoint position)
    : Animatable(position),
      sprites_(sprites),
      sprite_(0) {
}

SimpleItem::~SimpleItem() {
  for (int i = 0; i < sprites_.size(); i++) {
    ResourceLoader::Instance().ReleaseResource(sprites_[i].texture());
  }
}


// ViewEntity

void SimpleItem::Render() {
  sprites_[sprite_].DrawAtPointAngle(position(), angle());
}
