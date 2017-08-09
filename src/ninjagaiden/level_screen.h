//
//  level_screen.h
//  Proto2
//
//  Created by Shaun West on 7/29/17.
//
//

#ifndef level_screen_h
#define level_screen_h

#include "screen_view.h"
#include "video/video_sdl.h"
#include "level.h"

class LevelScreen : public ScreenView
{
public:
  // TODO can any of this be const?
  LevelScreen(GameSpec &game_spec, VideoSDL &video);
  void update(GameSpec &game_spec, float elapsed);
  void render(const GameSpec &game_spec) const;
private:
  Level level;
  VideoSDL &video;
};

typedef std::unique_ptr<LevelScreen, ScreenViewDeleter> ULevelScreen;

#endif
