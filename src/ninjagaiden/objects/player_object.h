//
//  player_object.h
//  Proto2
//
//  Created by Shaun West on 7/24/17.
//
//
// TODO rename objects folder to object


#ifndef player_object_h
#define player_object_h

#include "sprite/sprite.h"
#include "sprite/sprite_animator.h"
#include "world/layers.h"
#include "video/video_sdl.h"
#include "control/nes_input_manager.h"
#include "ninjagaiden/camera_manager.h"

class PlayerObject
{
public:
  PlayerObject(Sprite &sprite, SpriteFrameset &frameset, VideoSDL &video);
  //void update(Level &level, const NESInput &input, float elapsed);
  void update(const Layers &layers, const NESInput &input, float elapsed);
  void render(const Camera &camera) const;
private:
  void update_collisions(const Recti &new_hitbox, const Recti &old_hitbox, const Layers &layers);
  void update_animation(float elapsed);
  void update_movement(Vector2f &acceleration, const NESInput &input);
  void update_jump(Physics &physics, PhysicsFlags &flags, const NESInput &input);
  Vector2i get_position(Sprite &player);
  Recti get_hitbox(Vector2i position, const Recti &bounds);
private:
  Sprite &sprite;
  SpriteFrameset &frameset;
  VideoSDL &video;
  UniqueTexture playerImage;
  SpriteAnimator animator;
};

typedef std::vector<PlayerObject> PlayerObjectList;

#endif
