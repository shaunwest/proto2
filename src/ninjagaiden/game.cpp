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

Game::Game() {}

Game::Game(GameSpec game_spec) : game_spec(game_spec) {}

int Game::start() {
  // Init video
  VideoSDL video(game_spec.window, game_spec.asset_paths);
  
  // Init input
  NESInputManager input_manager;
  
  // Init screens
  TitleScreen title_screen = TitleScreen(video);
  
  bool quit = false;

  while (!quit) {
    bool render = false;

    while (timer.do_updates()) {
      render = true;

      SDL_Event sdl_event;
      while(SDL_PollEvent(&sdl_event)) {
        switch (sdl_event.type) {
          case SDL_QUIT: {
            std::cout << "SDL Quit Event" << std::endl;
            quit = true;
            break;
          }
        }
      }
      
      input_manager.update(game_spec.input);
      
      // Debug ESC to quit
      NESInput input_action = game_spec.input;
      if (input_action.esc) {
        std::cout << "ESC was pressed" << std::endl;
        quit = true;
      } else if (input_action.fullscreen && input_action.fullscreen_count > 15) {
        std::cout << "F was pressed" << std::endl;
        game_spec.window.fullscreen = !game_spec.window.fullscreen;
        game_spec.input.fullscreen_count = 0;
        video.init_window(game_spec.window);
      }
      
      // UPDATE
      switch(game_spec.current_screen) {
        case TITLE_SCREEN: {
          
          TitleAction title_action = title_screen.update(game_spec.input);
          if (title_action == TITLE_START) {
            game_spec.current_screen = LEVEL_SCREEN;
            game_spec.current_level = LEVEL_1;
          }
          break;
        }
        case LEVEL_SCREEN: {
          // update(time_per_frame);
          std::cout << "update level";
          break;
        }
      }
    }
    
    // RENDER (when a full frame has passed)
    if (render) {
      video.render_begin();
      
      switch(game_spec.current_screen) {
      case TITLE_SCREEN:
        title_screen.render(video);
        break;
      case LEVEL_SCREEN:
        std::cout << "render level";
        break;
      }
      
      //renderer.render_string() << timer.print_time().str();
      video.render_string("FPS: " + std::to_string(timer.get_time()->fps), Vector{0, 0});
      video.render_end();
    }
  }

  return 0;
}
