//
//  timer.h
//  Proto2
//
//  Created by Shaun West on 6/11/17.
//
//

#ifndef timer_h
#define timer_h

#include <sstream>

struct Time {
  float time_since_last_frame = 0;
  int frame_count = 0;
  float total_time = 0;
  float fps = 0;
  float time_per_frame = 1.f/60.f;
  float elapsed = 0;
};

class GameTimer {
public:
  GameTimer();
  GameTimer(Time t);
  bool do_updates();
  Time &get_time();
  float get_total_time();
  std::ostringstream print_time();

public:
  constexpr static float ONE_SECOND = 1000;

private:
  Time time;
  bool frame_ready;
};

#endif /* timer_h */
