//
//  enemy_object.h
//  Proto2
//
//  Created by Shaun West on 8/22/17.
//

#ifndef enemy_object_h
#define enemy_object_h

#include "video/video_sdl.h"
#include "world/layers.h"
#include "sprite_object.h"
#include "sprite/sprite.h"
#include "sprite/sprite_animator.h"

class EnemyObject : public SpriteObject
{
public:
  EnemyObject(Sprite &sprite, SpriteFrameset &frameset, VideoSDL &video);
  void update(Layers &layers, float elapsed);
  void render() const;
private:
  SpriteFrameset &frameset;
  VideoSDL &video;
  UniqueTexture image;
  SpriteAnimator animator;
};

#endif
