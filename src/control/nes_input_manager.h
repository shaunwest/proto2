//
//  nes_input_manager.h
//  Proto2
//
//  Created by Shaun West on 6/14/17.
//
//

#ifndef nes_input_manager_h
#define nes_input_manager_h

struct NESInput {
  bool up = false;
  int up_count = 0;
  bool down = false;
  int down_count = 0;
  bool left = false;
  int left_count = 0;
  bool right = false;
  int right_count = 0;
  bool start = false;
  int start_count = 0;
  bool select = false;
  int select_count = 0;
  bool debug_esc = false;
};


class NESInputManager {
public:
  NESInputManager();
  void update(NESInput &nes_input);
};

#endif /* nes_input_manager_h */
