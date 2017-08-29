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
  LevelScreen(std::string levelPath, GameConfig &config, VideoSDL &video);
  void update(ViewMode &view_mode, const NESInput &input, float elapsed);
  void render() const;
  ~LevelScreen();
private:
  LevelManager * levelManager;
  VideoSDL &video;
};

typedef std::unique_ptr<LevelScreen, ScreenDeleter> ULevelScreen;

#endif
