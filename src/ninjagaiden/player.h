//
//  player.h
//  Proto2
//
//  Created by Shaun West on 7/24/17.
//
//

#ifndef player_h
#define player_h

#include "spec.h"
#include "video/video_sdl.h"
#include "sprite/sprite_animator.h"
#include "control/nes_input_manager.h"

class Player
{
public:
  Player();
  Player(SpriteFrameset &frameset, VideoSDL &video);
  void update(Sprite &player, SpriteFrameset &frameset, const NESInput &input, float elapsed);
  void render(const Sprite &player, const SpriteFrameset &frameset, const CameraSpec &camera) const;
private:
  void update_movement(PhysicsSpec &physics, const Vector2i position, const NESInput &input);
  void update_jump(PhysicsSpec &physics, PhysicsFlags &flags, const NESInput &input);
  UniqueTexture playerImage;
  VideoSDL &video;
  SpriteAnimator animator;
};

#endif
