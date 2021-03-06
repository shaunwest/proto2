//
//  sprite_object.h
//  Proto2
//
//  Created by Shaun West on 7/15/17.
//
//

#ifndef sprite_object_h
#define sprite_object_h

#include "util/log.h"
#include "sprite/sprite.h"
#include "world/layers.h"
#include "level/camera_manager.h"

class SpriteObject {
public:
  virtual void update(Layers &layers, float elapsed) {
    LOG(LOG_WARNING) << "SpriteObject::update not implemented";
  };
  virtual void render(const Camera &camera) const {
    LOG(LOG_WARNING) << "SpriteObject::render not implemented";
  };
  virtual ~SpriteObject() {};
};

typedef std::vector<SpriteObject *> SpriteObjectList;

#endif
