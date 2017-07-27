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

Player::Player(VideoSDL &video, AsepriteLoader &sprite_loader) {
  SpriteFrameset player = sprite_loader.load("assets/sprites/ryu.json", video);
}

int Player::update() { return 0; }

void Player::render(const VideoSDL &video) const {
  IntRect rsrc(0, 0, 64, 32);
  IntRect rdest(0, 0, 64, 32);
  video.render_image("assets/sprites/ryu.png", rsrc, rdest);
}
