//
//  game.cpp
//  Proto2
//
//  Created by Shaun West on 6/11/17.
//
//

#include "game.h"

#include "util/log.h"
#include "title_screen.h"
#include "level.h"

LogLevel Logger::reportingLevel = LOG_DEBUG;

Game::Game() {}

Game::Game(GameSpec game_spec) : game_spec(game_spec) {}

int Game::start() {
  // Init video
  VideoSDL video(game_spec.window);

  // Init input
  NESInputManager input_manager;

  // Init inital view
  UniqueView current_view = UniqueTitleScreen(new TitleScreen(video));

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
      switch(game_spec.current_view_id) {
        case VIEW_TITLE: {
          TitleAction title_action = (TitleAction)current_view->update(game_spec.input);

          switch (title_action) {
            case TITLE_ACTION_START:
              game_spec.current_view_id = VIEW_LEVEL;
              game_spec.current_level_id = LEVEL_1;
              current_view = UniqueLevel(new Level("levels/level1_1.json", video));
              break;
            case TITLE_ACTION_NONE:
              break;
          }

          break;
        }
        case VIEW_LEVEL: {
          LevelAction level_action = (LevelAction)current_view->update(game_spec.input);

          switch (level_action) {
            case LEVEL_ACTION_NONE:
              break;
          }

          // update(time_per_frame);
          std::cout << "update level" << std::endl;
          break;
        }
      }
    }

    // RENDER when a full frame has passed
    if (render) {
      video.render_begin();

      switch(game_spec.current_view_id) {
        case VIEW_TITLE:
          current_view->render(video);
          break;
        case VIEW_LEVEL:
          //std::cout << "render level" << std::endl;
          current_view->render(video);
          break;
      }

      //renderer.render_string() << timer.print_time().str();
      video.render_string("FPS: " + std::to_string(timer.get_time()->fps), IntVector2{0, 0});
      video.render_end();
    }
  }

  return 0;
}
