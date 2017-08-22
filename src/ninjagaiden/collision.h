//
//  collision.h
//  Proto2
//
//  Created by Shaun West on 8/12/17.
//
//

#ifndef collision_h
#define collision_h

#include "ninjagaiden/spec.h"
#include "util/geom.h"

class Collision
{
public:
  static Vector2i boxes(const Recti &new_hitbox, const Recti &old_hitbox, const CollisionBoxList &boxes);
private:
  static CollisionBoxList filter_box_intersections(const Recti &source, const CollisionBoxList &targets);
  static VectorListi get_deltas(const Recti &source, const RectListi &targets);
  static Vector2i get_delta(const Recti &source, const Recti &target);
  static VectorListi merge_deltas(VectorListi deltas);
  static Vector2i resolve_deltas(const VectorListi &deltas);
};

#endif
