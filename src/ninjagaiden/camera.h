//
//  camera.h
//  Proto2
//
//  Created by Shaun West on 7/24/17.
//
//

#ifndef camera_h
#define camera_h

#include "spec.h"

class Camera
{
public:
  void update(CameraSpec &camera, const Sprite &player);
};

#endif
