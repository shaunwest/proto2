//
//  game_manager.cpp
//  Proto2
//
//  Created by Shaun West on 6/11/17.
//
//

#include "game_manager.h"

#include "level_manager.h"
#include "util/log.h"
#include "screen.h"
#include "title_screen.h"
#include "level_screen.h"
#include "loader/tiled_loader.h"
#include "loader/aseprite_loader.h"

LogLevel Logger::reportingLevel = LOG_DEBUG;

GameManager::GameManager() {}

GameManager::GameManager(Game game) : game(game) {}

int GameManager::start() {
  // Init video
  VideoSDL video(game.window);

  // Init input
  NESInputManager input_manager;

  // Create our asset loaders
  TiledLoader level_loader;
  AsepriteLoader sprite_loader;

  // This will point to the current screen
  // Also, set current_screen mode to the title screen
  UScreen current_screen;
  game.view_mode = MODE_LOAD_TITLE;

  // Load some initial assets
  // TODO just put player in sprite_framesets as 0?
  game.level.player_frameset = sprite_loader.load("assets/sprites/ryu.json", video);
  game.level.sprite_framesets[1] = sprite_loader.load("assets/sprites/enemy.json", video);

  // Main game loop
  bool quit = false;

  while (!quit) {
    bool render = false;

    while (timer.do_updates()) {
      render = true;

      SDL_Event sdl_event;
      while(SDL_PollEvent(&sdl_event)) {
        switch (sdl_event.type) {
          case SDL_QUIT: {
            LOG(LOG_INFO) << "SDL Quit Event";
            quit = true;
            break;
          }
        }
      }

      // UPDATE

      // Check input
      input_manager.update(game.input);

      NESInput input_action = game.input;

      // Hit ESC to quit, F to toggle fullscreen
      if (input_action.esc) {
        LOG(LOG_INFO) << "ESC was pressed";
        quit = true;
      } else if (input_action.fullscreen && input_action.fullscreen_count > 15) {
        LOG(LOG_INFO) << "F was pressed";
        game.window.fullscreen = !game.window.fullscreen;
        game.input.fullscreen_count = 0;
        video.init_window(game.window);
      }

      // Handle current_screen modes
      switch (game.view_mode) {
        case MODE_LOAD_TITLE:
          current_screen = UTitleScreen(new TitleScreen(game, video));
          game.view_mode = MODE_UPDATE;
          break;
        case MODE_LOAD_LEVEL_1:
          game.level.layers = level_loader.load("levels/level1_1.json");
          current_screen = ULevelScreen(new LevelScreen(game, video));
          game.view_mode = MODE_UPDATE;
          break;
        case MODE_UPDATE:
          current_screen->update(game, timer.get_time().elapsed);
          break;
      }
    }

    // RENDER when a full frame has passed
    if (render) {
      video.render_begin();
      current_screen->render(game);
      //renderer.render_string() << timer.print_time().str();
      video.render_string("FPS: " + std::to_string(timer.get_time().fps), Vector2i{0, 0});
      video.render_string("CAM: " + std::to_string(game.level.camera.position.x), Vector2i{0, 20});
      //std::cout << timer.get_time().elapsed << std::endl;
      video.render_end();
    }
  }

  return 0;
}
