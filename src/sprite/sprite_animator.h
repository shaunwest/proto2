//
//  sprite_animator.h
//  Proto2
//
//  Created by Shaun West on 7/26/17.
//
//

#ifndef sprite_animator_h
#define sprite_animator_h

#include "video/video_sdl.h"

#include "sprite.h"

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

class SpriteAnimator
{
public:
  SpriteAnimator();
  void update(SpriteAnimation &sprite_animation, SpriteFrameset &frameset, float elapsed);
};

#endif
