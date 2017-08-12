//
//  player.cpp
//  Proto2
//
//  Created by Shaun West on 7/24/17.
//
//
// TODO player animations
// TODO then make camera follow player

#include "player.h"

#include "util/geom.h"
#include "physics.h"

Player::Player(SpriteFrameset &frameset, VideoSDL &video) : video(video) {
  playerImage = video.create_image(frameset.image_path);
}

void Player::update(Sprite &player, SpriteFrameset &frameset, const NESInput &input, float elapsed) {
  update_movement(player.physics, player.position, input);
  //update_jump(player.physics, player.flags, input);

  // Set velocity
  player.physics.velocity = Physics::move(player.physics, elapsed);

  // Set position
  player.position = Vector2i(
    player.position.x + round(player.physics.velocity.x),
    player.position.y + round(player.physics.velocity.y)
  );

  // Do animation stuff
  if (player.physics.velocity.x > 0) {
    player.animation.current_sequence = "walk";
    player.dir = DIR_RIGHT;
  } else if (player.physics.velocity.x < 0) {
    player.animation.current_sequence = "walk";
    player.dir = DIR_LEFT;
  } else {
    player.animation.current_sequence = "idle";
  }

  player.animation.flip = (player.dir == DIR_LEFT);

  animator.update(player.animation, frameset, elapsed);
}

void Player::update_movement(PhysicsSpec &physics, const Vector2i position, const NESInput &input) {
  constexpr int move_delta = 125;

  // Check input and apply acceleration
  if (input.right) {
    physics.acceleration.x = move_delta;
  } else if (input.left) {
    physics.acceleration.x = -move_delta;
  } else {
    physics.acceleration.x = 0;
  }
}

// TODO WIP needs collisions
void Player::update_jump(PhysicsSpec &physics, PhysicsFlags &flags, const NESInput &input) {
  constexpr int jump_delta = 1300; //650;

  if (!input.up) { // && flags.colliding_with_floor) {
    flags.jump_cancel = false;
  }

  if (/*flags.colliding_with_floor && */ !flags.jump_cancel) {
    int jump_accel = (input.up) ? -jump_delta : 0;
    if (jump_accel < 0) {
      flags.jump_cancel = true;
      physics.acceleration.y = jump_accel;
    }
  }
}

void Player::render(const Sprite &player, const SpriteFrameset &frameset, const CameraSpec &camera) const {
  SpriteFrame frame = frameset.frames.at(
      player.animation.current_sequence)[player.animation.current_sequence_index];

  Recti rsrc(frame.atlas_x, frame.atlas_y, player.size.width, player.size.height);
  Recti rdest(
    player.position.x - camera.position.x, player.position.y - camera.position.y,
    player.size.width, player.size.height
  );

  video.render_texture(playerImage.get(), rsrc, rdest, player.animation.flip);
}
