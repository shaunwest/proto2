//
//  enemy_object.cpp
//  Proto2
//
//  Created by Shaun West on 8/22/17.
//
//

#include "enemy_object.h"

EnemyObject::EnemyObject(Sprite &sprite, SpriteFrameset &frameset, VideoSDL &video) :
  frameset(frameset),
  video(video) {
  image = video.create_image(frameset.image_path);
}

void EnemyObject::update(Layers &layers, float elapsed) {

}

void EnemyObject::render() const {

}
