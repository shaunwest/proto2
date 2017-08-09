//
//  game.cpp
//  Proto2
//
//  Created by Shaun West on 6/11/17.
//
//

#include "game.h"

#include "level.h"
#include "util/log.h"
#include "screen_view.h"
#include "title_screen.h"
#include "level_screen.h"
#include "loader/tiled_loader.h"
#include "loader/aseprite_loader.h"

LogLevel Logger::reportingLevel = LOG_DEBUG;

Game::Game() {}

Game::Game(GameSpec game_spec) : game_spec(game_spec) {}

int Game::start() {
  // Init video
  VideoSDL video(game_spec.window);

  // Init input
  NESInputManager input_manager;

  // Create our asset loaders
  TiledLoader level_loader;
  AsepriteLoader sprite_loader;

  // This will point to the current screen/
  // Also, set view mode to the title screen
  UScreenView view;
  game_spec.view_mode = MODE_LOAD_TITLE;

  // Load some initial assets
  game_spec.level_spec.player_frameset = sprite_loader.load("assets/sprites/ryu.json", video);

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
      input_manager.update(game_spec.input);

      NESInput input_action = game_spec.input;

      // Hit ESC to quit, F to toggle fullscreen
      if (input_action.esc) {
        LOG(LOG_INFO) << "ESC was pressed";
        quit = true;
      } else if (input_action.fullscreen && input_action.fullscreen_count > 15) {
        LOG(LOG_INFO) << "F was pressed";
        game_spec.window.fullscreen = !game_spec.window.fullscreen;
        game_spec.input.fullscreen_count = 0;
        video.init_window(game_spec.window);
      }

      // Handle view modes
      switch (game_spec.view_mode) {
        case MODE_LOAD_TITLE:
          view = UTitleScreen(new TitleScreen(game_spec, video));
          game_spec.view_mode = MODE_UPDATE;
          break;
        case MODE_LOAD_LEVEL_1:
          game_spec.level_spec.layers = level_loader.load("levels/level1_1.json");
          view = ULevelScreen(new LevelScreen(game_spec, video));
          game_spec.view_mode = MODE_UPDATE;
          break;
        case MODE_UPDATE:
          view->update(game_spec, timer.get_time().elapsed);
          break;
      }
    }

    // RENDER when a full frame has passed
    if (render) {
      video.render_begin();
      view->render(game_spec);
      //renderer.render_string() << timer.print_time().str();
      video.render_string("FPS: " + std::to_string(timer.get_time().fps), IntVector2{0, 0});
      video.render_end();
    }
  }

  return 0;
}
