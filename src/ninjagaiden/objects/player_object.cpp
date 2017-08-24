//
//  player_object.cpp
//  Proto2
//
//  Created by Shaun West on 7/24/17.
//
//

#include "player_object.h"

#include "util/geom.h"
#include "ninjagaiden/action.h"
#include "ninjagaiden/collision.h"

PlayerObject::PlayerObject(Sprite &player, SpriteFrameset &frameset, VideoSDL &video) :
  player(player), frameset(frameset), video(video) {
  playerImage = video.create_image(frameset.image_path);
}

// FIXME: need to adjust collisions because coordinates don't take HUD into consideration.
// made a temporary fix in tiled_loader.cpp
//void PlayerObject::update(Level &level, const NESInput &input, float elapsed) {
void PlayerObject::update(Layers &layers, const NESInput &input, float elapsed) {
  // Update left & right acceleration
  update_movement(player.physics.acceleration, input);

  // Apply gravity
  player.physics.acceleration.y = 125; // gravity

  // Update vertical acceleration
  update_jump(player.physics, player.flags, input);

  // Update velocity based on acceleration
  player.physics.velocity = Action::move(player.physics, elapsed);

  // Get the player's hitbox based on their current, unmodified position
  Recti hitbox = get_hitbox(player.position, player.bounds);

  // Get the position the player intends to get to
  Vector2i target_position = get_position(player);

  // Get the player's proposed new hitbox, given intended position
  Recti new_hitbox = get_hitbox(target_position, player.bounds);

  // Adjust accel, velocity, and flags based on any collisions that happen
  update_collisions(player, new_hitbox, hitbox, layers);

  // Update the player's position based on everything that's happened
  player.position = get_position(player);

  // Update the player's animation type and frame
  update_animation(player, frameset, elapsed);
}

// Check input and apply acceleration
void PlayerObject::update_movement(Vector2f &acceleration, const NESInput &input) {
  constexpr int move_delta = 125;

  if (input.right) {
    acceleration.x = move_delta;
  } else if (input.left) {
    acceleration.x = -move_delta;
  } else {
    acceleration.x = 0;
  }
}

void PlayerObject::update_collisions(Sprite &sprite, const Recti &new_hitbox, const Recti &old_hitbox, const Layers &layers) {
  Vector2i boxes_resolution = Collision::boxes(new_hitbox, old_hitbox, layers.collision_layer.boxes);

  // Halt if hit wall
  if (boxes_resolution.x != 0) {
    sprite.physics.velocity.x = 0;
    sprite.physics.acceleration.x = 0;
  }

  // Halt if hit ceiling or floor
  if (boxes_resolution.y != 0) {
    sprite.physics.velocity.y = 0;
    sprite.physics.acceleration.y = 0;
  }

  sprite.flags.colliding_with_ceiling = (boxes_resolution.y > 0);
  sprite.flags.colliding_with_floor = (boxes_resolution.y < 0);
  sprite.flags.colliding_with_left_wall = (boxes_resolution.x > 0);
  sprite.flags.colliding_with_right_wall = (boxes_resolution.x < 0);
}

void PlayerObject::update_jump(Physics &physics, PhysicsFlags &flags, const NESInput &input) {
  constexpr int jump_delta = 1300; //650;

  if (!input.up && flags.colliding_with_floor) {
    flags.jump_cancel = false;
  }

  if (flags.colliding_with_floor && !flags.jump_cancel) {
    int jump_accel = (input.up) ? -jump_delta : 0;
    if (jump_accel < 0) {
      flags.jump_cancel = true;
      physics.acceleration.y = jump_accel;
    }
  }
}

void PlayerObject::update_animation(Sprite &player, SpriteFrameset &frameset, float elapsed) {
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

Recti PlayerObject::get_hitbox(Vector2i position, const Recti &bounds) {
  int left = position.x + bounds.left;
  int top = position.y + bounds.top;
  int width = bounds.width; //bounds.right - bounds.left;
  int height = bounds.height; //bounds.bottom - bounds.top;

  return Recti(left, top, width, height);
}

Vector2i PlayerObject::get_position(Sprite &player) {
  return Vector2i(
    player.position.x + round(player.physics.velocity.x),
    player.position.y + round(player.physics.velocity.y)
  );
}

void PlayerObject::render(const CameraSpec &camera) const {
  SpriteFrame frame = frameset.frames.at(
      player.animation.current_sequence)[player.animation.current_sequence_index];

  Recti rsrc(frame.atlas_x, frame.atlas_y, player.size.width, player.size.height);
  Recti rdest(
    player.position.x - camera.position.x, player.position.y - camera.position.y,
    player.size.width, player.size.height
  );

  video.render_texture(playerImage.get(), rsrc, rdest, player.animation.flip);
}
