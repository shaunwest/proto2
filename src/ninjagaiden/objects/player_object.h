//
//  player_object.h
//  Proto2
//
//  Created by Shaun West on 7/24/17.
//
//

#ifndef player_object_h
#define player_object_h

#include "ninjagaiden/spec.h"
#include "video/video_sdl.h"
#include "sprite/sprite_animator.h"
#include "control/nes_input_manager.h"

class PlayerObject
{
public:
  PlayerObject();
  PlayerObject(Sprite &player, SpriteFrameset &frameset, VideoSDL &video);
  //void update(Level &level, const NESInput &input, float elapsed);
  void update(Layers &layers, const NESInput &input, float elapsed);
  void render(const CameraSpec &camera) const;
private:
  void update_collisions(Sprite &sprite, const Recti &new_hitbox, const Recti &old_hitbox, const Layers &layers);
  void update_animation(Sprite &player, SpriteFrameset &frameset, float elapsed);
  void update_movement(Vector2f &acceleration, const NESInput &input);
  void update_jump(Physics &physics, PhysicsFlags &flags, const NESInput &input);
  Vector2i get_position(Sprite &player);
  Recti get_hitbox(Vector2i position, const Recti &bounds);
  UniqueTexture playerImage;
  VideoSDL &video;
  SpriteAnimator animator;
  Sprite &player;
  SpriteFrameset &frameset;
};

#endif
