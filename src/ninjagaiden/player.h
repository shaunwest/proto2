//
//  player.h
//  Proto2
//
//  Created by Shaun West on 7/24/17.
//
//

#ifndef player_h
#define player_h

#include "loader/aseprite_loader.h"
#include "video/video_sdl.h"

class Player
{
public:
  Player();
  Player(VideoSDL &video, AsepriteLoader &sprite_loader);
  int update();
  void render(const VideoSDL &video) const;
};

#endif
