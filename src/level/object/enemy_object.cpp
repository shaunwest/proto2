//
//  enemy_object.cpp
//  Proto2
//
//  Created by Shaun West on 8/22/17.
//
//

#include "enemy_object.h"

EnemyObject::EnemyObject(Sprite &sprite, SpriteFrameset &frameset, VideoSDL &video) :
  sprite(sprite),
  frameset(frameset),
  video(video) {
  image = video.create_image(frameset.image_path);
  sprite.animation.current_sequence = "walk";
  sprite.animation.current_sequence_index = 0;
  sprite.animation.flip = true;
}

void EnemyObject::update(Layers &layers, float elapsed) {
  animator.update(sprite.animation, frameset, elapsed);
}

void EnemyObject::render(const Camera &camera) const {
  SpriteFrame frame = frameset.frames.at(
      sprite.animation.current_sequence)[sprite.animation.current_sequence_index];

  Recti rsrc(frame.atlas_x, frame.atlas_y, sprite.size.width, sprite.size.height);
  Recti rdest(
    sprite.position.x - camera.position.x, (sprite.position.y) - camera.position.y,
    sprite.size.width, sprite.size.height
  );

  video.render_texture(image.get(), rsrc, rdest, sprite.animation.flip);
}
