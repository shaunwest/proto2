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
#include "game/level_data.h"

class SpriteAnimator
{
public:
  SpriteAnimator();
  void update(SpriteAnimation &sprite_animation, SpriteFrameset &frameset, float elapsed);
};

#endif
