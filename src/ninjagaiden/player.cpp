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

Player::Player() {}

/*
Player::Player() {
  // TODO Framesets should probably be stored on data model not in individual objects. Framesets should be stored with ids. Ids need to be linked to SpriteAnimations
  //SpriteFrameset player_frameset = sprite_loader.load("assets/sprites/ryu.json", video);
}
*/

int Player::update(Sprite &player_data, float elapsed) {
  return 0;
}

void Player::render(const Sprite &player_data, SpriteFrameset &frameset, const VideoSDL &video) const {
  IntRect rsrc(0, 0, 64, 32);
  IntRect rdest(0, 0, 64, 32);
  //video.render_image("assets/sprites/ryu.png", rsrc, rdest);
}
