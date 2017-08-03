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
#include "game/level_view.h"
#include "game/screen_view.h"
#include "screen_dispatcher.h"
#include "level_dispatcher.h"

LogLevel Logger::reportingLevel = LOG_DEBUG;

Game::Game() {}

Game::Game(GameSpec game_spec) : game_spec(game_spec) {}

int Game::start() {
  // Init video
  VideoSDL video(game_spec.window);

  // Init input
  NESInputManager input_manager;

  // Create dispatchers
  //UniqueScreenDispatcher screen_dispatcher = UniqueScreenDispatcher(new ScreenDispatcher(video));
  ScreenDispatcher screen_dispatcher(video);
  LevelDispatcher level_dispatcher(video);

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

      input_manager.update(game_spec.input);

      // Hit ESC to quit, F to toggle fullscreen
      NESInput input_action = game_spec.input;
      if (input_action.esc) {
        LOG(LOG_INFO) << "ESC was pressed";
        quit = true;
      } else if (input_action.fullscreen && input_action.fullscreen_count > 15) {
        LOG(LOG_INFO) << "F was pressed";
        game_spec.window.fullscreen = !game_spec.window.fullscreen;
        game_spec.input.fullscreen_count = 0;
        video.init_window(game_spec.window);
      }

      // UPDATE
      // TODO: make all levels and screens derive from single View class. Pass full GameSpec to 
      // update and render (and create?)
      switch (game_spec.view_mode) {
        case VIEW_SCREEN: {
          ScreenDispatch dispatch = screen_dispatcher.update(game_spec.screen_id, game_spec.input);

          switch (dispatch) {
            case SCREEN_DISPATCH_START_GAME:
              game_spec.view_mode = VIEW_LEVEL;
              game_spec.level_spec.level_id = LEVEL_1;
              break;
            case SCREEN_DISPATCH_NONE:
              break;
          }

          break;
        }
        case VIEW_LEVEL: {
          LevelDispatch dispatch = level_dispatcher.update(game_spec.level_spec, game_spec.input);

          switch (dispatch) {
            case LEVEL_DISPATCH_NONE:
              break;
          }

          break;
        }
      }
    }

    // RENDER when a full frame has passed
    if (render) {
      video.render_begin();

      switch(game_spec.view_mode) {
        case VIEW_SCREEN:
          screen_dispatcher.render(game_spec.screen_id);
          break;
        case VIEW_LEVEL:
          level_dispatcher.render(game_spec.level_spec);
          break;
      }

      //renderer.render_string() << timer.print_time().str();
      video.render_string("FPS: " + std::to_string(timer.get_time()->fps), IntVector2{0, 0});
      video.render_end();
    }
  }

  return 0;
}
