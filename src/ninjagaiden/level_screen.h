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
#include "video/video_sdl.h"
#include "level_manager.h"

class LevelScreen : public Screen
{
public:
  // TODO can any of this be const?
  LevelScreen(Game &game, VideoSDL &video);
  void update(Game &game, float elapsed);
  void render(const Game &game) const;
private:
  LevelManager levelManager;
  VideoSDL &video;
};

typedef std::unique_ptr<LevelScreen, ScreenDeleter> ULevelScreen;

#endif
