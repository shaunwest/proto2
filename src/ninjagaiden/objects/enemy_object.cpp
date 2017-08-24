//
//  enemy_object.cpp
//  Proto2
//
//  Created by Shaun West on 8/22/17.
//
//

#include "enemy_object.h"

EnemyObject::EnemyObject(SpriteFrameset &frameset, VideoSDL &video) : video(video) {
  image = video.create_image(frameset.image_path);
}

void EnemyObject::update(Sprite &sprite, Layers &layers, float elapsed) {

}

void EnemyObject::render(const Sprite &sprite, const SpriteFrameset &frameset) const {

}
