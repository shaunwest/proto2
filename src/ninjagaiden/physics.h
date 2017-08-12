//
//  physics.h
//  Proto2
//
//  Created by Shaun West on 8/8/17.
//
//

#ifndef physics_h
#define physics_h

#include "spec.h"

class Physics
{
public:
  static Vector2f move(const PhysicsSpec &physics, float elapsed);
  static Vector2f propel(const Vector2f &vel, const Vector2f &accel, float elapsed);
  static Vector2f decelerate(const Vector2f &vel, const Vector2f &accel, const Vector2f &momentum, float elapsed);
  static Vector2f halt(const Vector2f &vel, const Vector2f &min);
  static Vector2f clamp(const Vector2f &vel, const PhysicsAttributes &attrs);
};

#endif
