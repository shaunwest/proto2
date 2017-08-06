//
//  sprite_animator.cpp
//  Proto2
//
//  Created by Shaun West on 7/24/17.
//
#include "sprite_animator.h"

#include "util/log.h"

SpriteAnimator::SpriteAnimator() {}

void SpriteAnimator::update(SpriteAnimation &sprite_animation, SpriteFrameset &frameset, float elapsed) {
  std::string sequence_name = sprite_animation.current_sequence;

  if (frameset.frames.count(sequence_name) == 0) {
    LOG(LOG_ERROR) << "Frame sequence '" << sequence_name << "' does not exist!";
  }

  if (sprite_animation.current_sequence_index > frameset.frames[sequence_name].size() - 1) {
    sprite_animation.current_sequence_index = 0;
    sprite_animation.duration_count = 0;
  }
  else {
    SpriteFrame frame = frameset.frames[sequence_name][sprite_animation.current_sequence_index];

    if (sprite_animation.duration_count >= frame.duration) {
      sprite_animation.duration_count -= frame.duration;

      if (sprite_animation.current_sequence_index < frameset.frames[sequence_name].size() - 1) {
        sprite_animation.current_sequence_index += 1;
      }
      else {
        sprite_animation.current_sequence_index = 0;
      }
    }
  }

  sprite_animation.duration_count += (elapsed * 1000);
}
