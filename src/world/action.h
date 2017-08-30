//
//  action.h
//  Proto2
//
//  Created by Shaun West on 8/8/17.
//
//

#ifndef action_h
#define action_h

#include "sprite/sprite.h"
#include "util/geom.h"

class Action
{
public:
  static Vector2f move(const Physics &physics, float elapsed);
  static Vector2f propel(const Vector2f &vel, const Vector2f &accel, float elapsed);
  static Vector2f decelerate(const Vector2f &vel, const Vector2f &accel, const Vector2f &momentum, float elapsed);
  static Vector2f halt(const Vector2f &vel, const Vector2f &min);
  static Vector2f clamp(const Vector2f &vel, const PhysicsAttributes &attrs);
};

#endif
