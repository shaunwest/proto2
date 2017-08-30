//
//  level_screen.h
//  Proto2
//
//  Created by Shaun West on 7/29/17.
//
//

#ifndef level_screen_h
#define level_screen_h

#include "screen.h"
#include "game.h"
#include "video/video_sdl.h"
#include "level/level_manager.h"

class LevelScreen : public Screen
{
public:
  LevelScreen(std::string levelPath, Game &game, VideoSDL &video);
  void update(ViewMode &view_mode, const NESInput &input, float elapsed);
  void render() const;
private:
  ULevelManager levelManager;
  VideoSDL &video;
};

typedef std::unique_ptr<LevelScreen, ScreenDeleter> ULevelScreen;

#endif
