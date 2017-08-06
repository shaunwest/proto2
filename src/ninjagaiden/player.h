//
//  player.h
//  Proto2
//
//  Created by Shaun West on 7/24/17.
//
//

#ifndef player_h
#define player_h

//#include "loader/aseprite_loader.h"
#include "video/video_sdl.h"
#include "sprite/sprite_animator.h"
#include "game/level_data.h"

class Player
{
public:
  Player();
  Player(SpriteFrameset &frameset, VideoSDL &video);
  void update(Sprite &player_spec, SpriteFrameset &frameset, float elapsed);
  void render(const Sprite &player_spec, const SpriteFrameset &frameset) const;
private:
  UniqueTexture playerImage;
  VideoSDL &video;
  SpriteAnimator animator;
};

#endif
