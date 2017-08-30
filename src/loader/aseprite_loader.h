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

#include "video/video_sdl.h"
#include "json/json.h"
#include "sprite/sprite_animator.h"

/*
// TODO I think these structs should be defined elsewhere, but independent of implementation
struct SpriteFrame {
  int atlas_x;
  int atlas_y;
  float duration;
  bool rotated;
};

typedef std::map<std::string, std::vector<SpriteFrame>> FrameMap;

struct SpriteFrameset {
  std::string image_path;
  int sprite_width;
  int sprite_height;
  FrameMap frames;
};

typedef std::map<int, SpriteFrameset> SpriteFramesets;
*/

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
