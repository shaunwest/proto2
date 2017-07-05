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
  // Init rendering
  RendererSDL renderer(game_spec.window, game_spec.asset_paths);
  
  if (!renderer.ready) {
    return 0;
  }
  
  // Init input
  NESInputManager input_manager;
  
  // Init screens
  TitleScreen title_screen(renderer);
  
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
      if (input_action.debug_esc) {
        std::cout << "ESC was pressed" << std::endl;
        quit = true;
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
      renderer.render_begin();
      
      switch(game_spec.current_screen) {
      case TITLE_SCREEN:
        title_screen.render(renderer);
        break;
      case LEVEL_SCREEN:
        std::cout << "render level";
        break;
      }
      
      renderer.render_string() << timer.print_time().str();
      renderer.render_end();
    }
  }

  return 0;
}
