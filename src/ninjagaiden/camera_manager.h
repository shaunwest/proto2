//
//  camera_manager.h
//  Proto2
//
//  Created by Shaun West on 7/24/17.
//
//

#ifndef camera_manager_h
#define camera_manager_h

#include "sprite/sprite.h"

struct Camera {
  Vector2i position;
  Size viewport;
};

class CameraManager
{
public:
  CameraManager(Camera &camera);
  void update(const Sprite &sprite);
private:
  Camera &camera;
};

#endif
