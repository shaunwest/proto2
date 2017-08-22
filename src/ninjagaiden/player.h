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
  void update(LevelSpec &level, const NESInput &input, float elapsed);
  void render(const Sprite &player, const SpriteFrameset &frameset, const CameraSpec &camera) const;
private:
  void update_collisions(Sprite &sprite, const Recti &new_hitbox, const Recti &old_hitbox, const Layers &layers);
  void update_animation(Sprite &player, SpriteFrameset &frameset, float elapsed);
  void update_movement(Vector2f &acceleration, const NESInput &input);
  void update_jump(PhysicsSpec &physics, PhysicsFlags &flags, const NESInput &input);
  Vector2i get_position(Sprite &player);
  Recti get_hitbox(Vector2i position, const Recti &bounds);
  UniqueTexture playerImage;
  VideoSDL &video;
  SpriteAnimator animator;
};

#endif
