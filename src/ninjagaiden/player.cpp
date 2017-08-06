//
//  player.cpp
//  Proto2
//
//  Created by Shaun West on 7/24/17.
//
//  Remember: The player object should handle player logic, but does not store player state
//
//
// TODO need a player to move around
// TODO player animations
// TODO then make camera follow player

#include "player.h"

#include "util/util.h"

Player::Player(SpriteFrameset &frameset, VideoSDL &video) : video(video) {
  playerImage = video.create_image2(frameset.image_path);
}

void Player::update(Sprite &player_spec, SpriteFrameset &frameset, float elapsed) {
  animator.update(player_spec.animation, frameset, elapsed);
}

void Player::render(const Sprite &player_spec, const SpriteFrameset &frameset) const {
  SpriteFrame frame = frameset.frames.at(
      player_spec.animation.current_sequence)[player_spec.animation.current_sequence_index];

  IntRect rsrc(frame.atlas_x, frame.atlas_y, player_spec.size.width, player_spec.size.height);
  IntRect rdest(
      player_spec.position.x, player_spec.position.y,
      player_spec.size.width, player_spec.size.height
  );

  video.render_texture(playerImage.get(), rsrc, rdest);
}
