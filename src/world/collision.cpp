//
//  collision.cpp
//  Proto2
//
//  Created by Shaun West on 8/12/17.

#include "collision.h"

// Note: sprite can get stuck in place between boxes on opposite corners.
// e.g. simultaneous collision with BL box and TR box
Vector2i Collision::boxes(const Recti &new_hitbox, const Recti &old_hitbox, const CollisionBoxList &boxes) {
  Vector2i boxes_resolution;
  CollisionBoxList::const_iterator it;
  const CollisionBoxList boxes_intersected = filter_box_intersections(new_hitbox, boxes);

  for (auto box : boxes_intersected) {
    bool cancel_x = false;
    bool cancel_y = false;

    Vector2i box_collision_result = get_delta(new_hitbox, box.rect);

    // Apply collision resolution based on where the player
    // is coming from. e.g. If the bottom of the player's hitbox
    // *was* above the target box and there's a collision beneath the player,
    // assume the player has hit the "floor".
    if ((box_collision_result.y < 0 && old_hitbox.bottom <= box.rect.top) ||
        (box_collision_result.y > 0 && old_hitbox.top >= box.rect.bottom)) {
      // If two box resolutions are on the same y-plane, set a flag to cancel the x-value.
      // This prevents fake walls on seams between adjacent boxes.
      if (boxes_resolution.y == box_collision_result.y) {
        cancel_x = true;
      }

      boxes_resolution.y = box_collision_result.y;  // Floor / Ceiling
    }

    if ((box_collision_result.x < 0 && old_hitbox.right <= box.rect.left) ||
        (box_collision_result.x > 0 && old_hitbox.left >= box.rect.right)) {
      if (boxes_resolution.x == box_collision_result.x) {
        cancel_y = true;
      }

      boxes_resolution.x = box_collision_result.x;  // Side
    }

    // If cancel flags are set, clear out appropriate resolution values.
    // They could get set again on the next loop?
    if (cancel_x) {
      boxes_resolution.x = 0;
    }

    if (cancel_y) {
      boxes_resolution.y = 0;
    }
  }

  // There are rare cases where x and y both have resolutions.
  // When this happens, favor the y resolution.
  // (Player is positioned on top of platform rather than hitting an invisible wall)
  if (boxes_intersected.size() == 1 && boxes_resolution.x == boxes_resolution.y) {
    boxes_resolution.x = 0;
  }

  return boxes_resolution;
}


// Return rects that source rect intersects with
CollisionBoxList Collision::filter_box_intersections(const Recti &source, const CollisionBoxList &targets) {
  CollisionBoxList intersections;
  CollisionBoxList::const_iterator it;

  for (auto target_box : targets) {
    if (intersects(source, target_box.rect)) {
      intersections.push_back(target_box);
    }
  }

  return intersections;
}

// Figure the overlap between source rect and each rect in the target rects set
VectorListi Collision::get_deltas(const Recti &source, const RectListi &targets) {
  RectListi::const_iterator it;
  VectorListi deltas;

  for (it = targets.begin(); it != targets.end(); ++it) {
    deltas.push_back(get_delta(source, *it));
  }

  return deltas;
}

// Find the overlap between two rects
Vector2i Collision::get_delta(const Recti &source, const Recti &target) {
  int left = target.right - source.left; // positive
  int right = target.left - source.right; // negative
  int top = target.bottom - source.top; // positive
  int bottom = target.top - source.bottom; // negative

  return Vector2i(
    abs(right) < abs(left) ? right : left,
    abs(bottom) < abs(top) ? bottom : top
  );
}

// Combine all deltas into one final combined delta
VectorListi Collision::merge_deltas(VectorListi deltas) {
  VectorListi new_deltas;

  while (!deltas.empty()) {
    Vector2i delta = deltas.back();
    deltas.pop_back();
    int count = deltas.size() - 1;

    while (count >= 0) {
      Vector2i comparison_delta = deltas[count];

      if (delta.x == comparison_delta.x) {
        delta.y = abs(delta.y) + abs(comparison_delta.y);
        deltas.pop_back();
      } else if (delta.y == comparison_delta.y) {
        delta.x = abs(delta.x) + abs(comparison_delta.x);
        deltas.pop_back();
      }

      count--;
    }

    new_deltas.push_back(delta);
  }

  return new_deltas;
}

Vector2i Collision::resolve_deltas(const VectorListi &deltas) {
  VectorListi::const_iterator it;
  Vector2i resolution;

  for (it = deltas.begin(); it != deltas.end(); ++it) {
    Vector2i delta = (*it);

    if (abs(delta.x) < abs(delta.y)) {
      resolution.x = delta.x;
    } else {
      resolution.y = delta.y;
    }
  }

  return resolution;
}
