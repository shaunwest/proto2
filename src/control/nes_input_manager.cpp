//
//  nes_input_manager.cpp
//  Proto2
//
//  Created by Shaun West on 6/14/17.
//
//

#include "nes_input_manager.h"

#include "SDL.h"

NESInputManager::NESInputManager() {}

void NESInputManager::update(NESInput &nes_input) {
  const Uint8* keyflagss = SDL_GetKeyboardState(NULL);

  nes_input.up = keyflagss[SDL_SCANCODE_UP];
  nes_input.down = keyflagss[SDL_SCANCODE_DOWN];
  nes_input.left = keyflagss[SDL_SCANCODE_LEFT];
  nes_input.right = keyflagss[SDL_SCANCODE_RIGHT];
  nes_input.start = keyflagss[SDL_SCANCODE_RETURN];
  nes_input.esc = keyflagss[SDL_SCANCODE_ESCAPE];

  nes_input.fullscreen = keyflagss[SDL_SCANCODE_F];
  nes_input.fullscreen_count = (nes_input.fullscreen) ?
    nes_input.fullscreen_count + 1 : 0;
}
