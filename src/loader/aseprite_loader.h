//
//  aseprite_loader.h
//  Proto2
//
//  Created by Shaun West on 7/25/17.
//
//

#ifndef aseprite_loader_h
#define aseprite_loader_h

#include <iostream>

#include "game/level_data.h"
#include "video/video_sdl.h"
#include "json/json.h"

class AsepriteLoader
{
public:
  AsepriteLoader();
  SpriteFrameset load(std::string json_path, VideoSDL &video);
private:
  SpriteFrameset get_frameset(Json::Value frameset_config, VideoSDL &video);
  SpriteFrame get_frame(Json::Value frame_config);
};

#endif
