//
//  geom.cpp
//  Proto2
//
//  Created by Shaun West on 8/12/17.
//
//

#include "geom.h"

bool intersects(Recti rect1, Recti rect2) {
  return !(rect1.right <= rect2.left ||
          rect1.bottom <= rect2.top ||
          rect1.left >= rect2.right ||
          rect1.top >= rect2.bottom);
}
