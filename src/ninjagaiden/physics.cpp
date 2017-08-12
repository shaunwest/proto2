//
//  physics.cpp
//  Proto2
//
//  Created by Shaun West on 8/8/17.

#include "physics.h"

#include <math.h>

#include "util/log.h"

Vector2f Physics::move(const PhysicsSpec &physics, float elapsed) {
  Vector2f velocity = propel(physics.velocity, physics.acceleration, elapsed);

  velocity = decelerate(
    velocity,
    physics.acceleration,
    Vector2f(125, 125), // TODO move to PhysicsSpec
    elapsed
  );

  velocity = halt(velocity, {1, 1});
  velocity = clamp(velocity, physics.attrs);

  return velocity;
}

Vector2f Physics::propel(const Vector2f &vel, const Vector2f &accel, float elapsed) {
  Vector2f new_velocity = vel;

  new_velocity.x += (accel.x * elapsed);
  new_velocity.y += (accel.y * elapsed);

  return new_velocity;
}

// If there's no acceleration, start deceleration
Vector2f Physics::decelerate(const Vector2f &vel, const Vector2f &accel, const Vector2f &momentum, float elapsed) {
  Vector2f new_velocity = vel;

  if (accel.x == 0) {
    if (vel.x > 0) {
      new_velocity.x -= (momentum.x * elapsed);
    } else if (vel.x < 0) {
      new_velocity.x += (momentum.x * elapsed);
    }
  }

  if (accel.y == 0) {
    if (vel.y > 0) {
      new_velocity.y -= (momentum.y * elapsed);
    } else if (vel.y < 0) {
      new_velocity.y += (momentum.y * elapsed);
    }
  }

  return new_velocity;
}

// If velocity falls below a target value, just reset to zero
Vector2f Physics::halt(const Vector2f &vel, const Vector2f &min) {
  Vector2f new_velocity = vel;

  if (fabs(new_velocity.x) < min.x) {
    new_velocity.x = 0;
  }

  if (fabs(new_velocity.y) < min.y) {
    new_velocity.y = 0;
  }

  return new_velocity;
}

// Keep velocity from increasing beyond a given maximum
Vector2f Physics::clamp(const Vector2f &vel, const PhysicsAttributes &attrs) {
  Vector2f new_velocity;

  new_velocity.x = (vel.x > 0) ?
    fmin(vel.x, attrs.move_max_speed) : fmax(vel.x, -attrs.move_max_speed);

  new_velocity.y = (vel.y > 0) ?
    fmin(vel.y, attrs.fall_max_speed) : fmax(vel.y, -attrs.jump_max_speed);

  return new_velocity;
}
