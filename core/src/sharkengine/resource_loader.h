//
//  resource_loader.h
//  SharkEngine
//
//  Created by Jon Sharkey on 2009-09-28.
//  Copyright 2009 Sharkable. All rights reserved.
//

#ifndef SHARKENGINE_RESOURCELOADER_H_
#define SHARKENGINE_RESOURCELOADER_H_

#include <map>
#include <string>

#include "opengl/texture2d.h"

class AssetReader;
class SharkEngine;

class ResourceLoader {
 public:
  ResourceLoader(SharkEngine &shark_engine);

  Texture2D TextureWithName(const std::string &name);
  void ReleaseResource(const std::string &name);
  void ReleaseResource(Texture2D resource);
  void ReloadTextures();

  void set_texture_name_extention(std::string const & extention) {
    texture_name_extention_ = extention;
  }
  std::string const & texture_name_extention() { return texture_name_extention_; }

 private:
  Texture2D Texture(std::string filename, int opengl_id = 0);

  SharkEngine &shark_engine_;
  std::string texture_name_extention_;
  std::map<std::string, Texture2D> resources_;
  std::map<std::string, int> resource_counter_;
};

#endif
