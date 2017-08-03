//
//  screen_dispatcher.cpp
//  Proto2
//
//  Created by Shaun West on 7/29/17.
//

#include "screen_dispatcher.h"

ScreenDispatcher::ScreenDispatcher(VideoSDL &video) : video(video) {}

ScreenDispatch ScreenDispatcher::update(ScreenId screen_id, const NESInput &input) {
  switch (screen_id) {
    case SCREEN_TITLE: {
      if (screen_view == nullptr) {
        screen_view = UniqueTitleScreen(new TitleScreen(video));
      }

      ScreenAction action = screen_view->update(input);

      switch (action) {
        case SCREEN_ACTION_START:
          screen_view = nullptr;
          return SCREEN_DISPATCH_START_GAME;
        case SCREEN_ACTION_NONE:
          return SCREEN_DISPATCH_NONE;
      }

      break;
    }
  }
}

void ScreenDispatcher::render(ScreenId screen_id) {
  if (screen_view != nullptr) {
    screen_view->render(video);
  }
}

/*
ScreenDispatch ScreenDispatcher::update(ScreenId screen_id, const NESInput &input) {
  switch (screen_id) {
    case SCREEN_TITLE: {
      // FIXME: need to create this first, but how do we know when it's created? When do we kill it?
      screen_view = TitleScreen(video);
      ScreenAction action = screen_view.update(input);

      switch (action) {
        case SCREEN_ACTION_START:
          return SCREEN_DISPATCH_START_GAME;
        case SCREEN_ACTION_NONE:
          return SCREEN_DISPATCH_NONE;
      }

      break;
    }
  }
}

void ScreenDispatcher::render(ScreenId screen_id) {
  screen_view.render(video);
}
*/
