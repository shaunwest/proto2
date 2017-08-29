//
//  level_screen.cpp
//  Proto2
//
//  Created by Shaun West on 7/29/17.
//

#define PLAYER_START_ANIMATION      "idle"
#define PLAYER_START_X              16
#define PLAYER_START_Y              186
#define PLAYER_WIDTH                32
#define PLAYER_HEIGHT               32
#define FRAMESET_DEFAULT_ID         0
#define ANIMATION_DEFAULT_DURATION  0
#define ANIMATION_START_INDEX       0
#define CAMERA_START_X              0
#define CAMERA_START_Y              0
#define CAMERA_VIEW_WIDTH           LOGICAL_WIDTH
#define CAMERA_VIEW_HEIGHT          176

#include "level_screen.h"

#include "loader/tiled_loader.h"
#include "loader/aseprite_loader.h"

LevelScreen::LevelScreen(std::string levelPath, GameConfig &config, VideoSDL &video) : video(video) {
  TiledLoader level_loader;
  AsepriteLoader sprite_loader;

  SpriteFramesets framesets;
  framesets[0] = sprite_loader.load("assets/sprites/ryu.json", video);
  framesets[1] = sprite_loader.load("assets/sprites/enemy.json", video);

  Level level = {
    framesets,
    level_loader.load(levelPath), // Layers
    {
      0, // Sprite frameset id
      "player",
      { // Animation
        FRAMESET_DEFAULT_ID,
        PLAYER_START_ANIMATION,
        ANIMATION_DEFAULT_DURATION,
        ANIMATION_START_INDEX,
        false // flip
      },
      { PLAYER_START_X, PLAYER_START_Y },
      { PLAYER_WIDTH, PLAYER_HEIGHT },
      DIR_RIGHT,
      { 10, 0, 12, 32 } // bounds
    },
    { // Camera
      { CAMERA_START_X, CAMERA_START_Y },
      { CAMERA_VIEW_WIDTH, CAMERA_VIEW_HEIGHT }
    }
  };

  levelManager = new LevelManager(level, video); // TODO needs to be deleted!
}

void LevelScreen::update(ViewMode &view_mode, const NESInput &input, float elapsed) {
  levelManager->update(input, elapsed);
}

void LevelScreen::render() const {
  levelManager->render();
}

LevelScreen::~LevelScreen() {
  delete levelManager;
}
