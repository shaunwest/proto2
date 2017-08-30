//
//  level_manager.h
//  Proto2
//
//  Created by Shaun West on 7/16/17.
//
//

#ifndef level_manager_h
#define level_manager_h

#include <iostream>

#include "object/player_object.h"
#include "object/sprite_object.h"
#include "camera_manager.h"
#include "control/nes_input_manager.h"
#include "video/video_sdl.h"

struct Level {
  SpriteFramesets sprite_framesets;
  Layers layers;
  Sprite player;
  Camera camera;
};

class LevelManager
{
public:
  LevelManager(Level level, VideoSDL &video);
  void update(const NESInput &nes_input, float elapsed);
  void render() const;
private:
  Level level;
  SpriteFramesets sprite_framesets;
  PlayerObject player_object;
  SpriteObjectList sprite_objects;
  UniqueTexture backgroundImage;
  VideoSDL &video;
  CameraManager camera_manager;
};

struct LevelManagerDeleter
{
  void operator()(LevelManager *lm) const {
    delete lm;
    LOG(LOG_INFO) << "Deleted LevelManager";
  }
};

typedef std::unique_ptr<LevelManager, LevelManagerDeleter> ULevelManager;

#endif
