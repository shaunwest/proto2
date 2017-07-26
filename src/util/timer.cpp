//
//  timer.cpp
//  Proto2
//
//  Created by Shaun West on 6/11/17.
//
//

#include "timer.h"

#include "SDL.h"

GameTimer::GameTimer() {
}

GameTimer::GameTimer(Time t) {
  time = t;
}

// If time passed is < target frame time, keep stepping (return false)
// If time passed is >= target frame time, allow a frame (return true)
bool GameTimer::do_updates() {
  if (!frame_ready) {
    time.elapsed = get_total_time() - time.total_time;
    time.time_since_last_frame += time.elapsed;
    time.total_time += time.elapsed;
    time.fps = time.frame_count / time.total_time;
  }

  frame_ready = (time.time_since_last_frame >= time.time_per_frame);

  if (frame_ready) {
    time.time_since_last_frame -= time.time_per_frame;
    time.frame_count++;
  }

  return frame_ready;
}

Time * GameTimer::get_time() {
  return &time;
}

float GameTimer::get_total_time() {
  return SDL_GetTicks() / ONE_SECOND;
}

std::ostringstream GameTimer::print_time() {
  std::ostringstream os;

  os
    << "FPS  : " << time.fps << std::endl
    << "TIME : " << time.total_time << std::endl
    << "FRMS : " << time.frame_count << std::endl;

  return os;
}
