//
//  camera_manager.cpp
//  Proto2
//
//  Created by Shaun West on 7/24/17.
//
//

#include "camera_manager.h"

CameraManager::CameraManager(Camera &camera) : camera(camera) {}

void CameraManager::update(const Sprite &sprite) {
  if ((sprite.position.x < 3200 &&
        sprite.physics.velocity.x > 0 &&
        (sprite.position.x - camera.position.x) > 128) ||
    (sprite.position.x > 128 &&
     sprite.physics.velocity.x < 0 &&
        (sprite.position.x - camera.position.x) < 128))
  {
    camera.position.x += sprite.physics.velocity.x;
  }
}
