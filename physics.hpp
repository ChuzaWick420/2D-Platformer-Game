#pragma once

#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

#include "Player.hpp"
#include "Hitbox.hpp"
#include "Level.hpp"

//returns index of hitbox that player is colliding with
int check_collision(Player& target, Level& tile) {

	//iterates over all hitboxes in the level
	for (std::vector<Hitbox>::iterator i = tile.hitboxes.begin(); i != tile.hitboxes.end(); i++) {

		//if player is colliding with a hitbox
		if (target.get_hitbox()->collides(*i)) {
			//return it's index
			return (i - tile.hitboxes.begin());
		}

	}

	//return -1 if no collision
	return -1;

}

std::string check_direction(Player& target, Hitbox& collider) {

	//collider is at bottom
	if (target.get_hitbox()->get_position().y + target.get_hitbox()->get_size().y - collider.get_size().y < collider.get_position().y && target.get_hitbox()->get_position().y + target.get_hitbox()->get_size().y > collider.get_position().y)
		return "Bottom";

	//collider is at right
	if (target.get_hitbox()->get_position().x + target.get_hitbox()->get_size().x / 2 < collider.get_position().x && target.get_hitbox()->get_position().x + target.get_hitbox()->get_size().x > collider.get_position().x)
		return "Right";

	//collider is at left
	if (target.get_hitbox()->get_position().x < collider.get_position().x + collider.get_size().x)
		return "Left";

	else
		return "Invalid";
}

void apply_gravity(Player& target, Level& tile, float& gravity_val) {

	//std::cout << "Velocity: " << target.get_jump_velocity() << ", Gravity: " << gravity_val << std::endl;

	//checks which hitbox player is colliding with
	int index = check_collision(target, tile);

	//if player is not colliding with floor
	if (index == -1) {

		target.on_ground = false;

		if (target.current_state == Player::Fall) {
			gravity_val += 0.03f;
			target.player_sprite.move(0, gravity_val);
		}

	}

	//if player is colliding with something
	if (index != -1) {

		//if player is touching bottom
		if (check_direction(target, tile.hitboxes[index]) == "Bottom" && target.current_state != Player::Jump) {

			gravity_val = 0;

			//move player up till it appears he is at top
 			target.player_sprite.setPosition(target.get_position().x, tile.hitboxes[index].get_position().y - target.player_sprite.getGlobalBounds().height / 2 + 10);

			//and anounce that he is on ground now
			target.on_ground = true;
			target.is_jumping = false;

			//reset vertical velocity
			target.set_jump_velocity(3);
		}
		
		else {

			target.on_ground = false;

			if (target.current_state == Player::Fall) {
				gravity_val += 0.03f;
				target.player_sprite.move(0, gravity_val);
			}

		}

		//if player is touching right wall
		if (check_direction(target, tile.hitboxes[index]) == "Right") {
			//move player left till it appears he is at left of the wall
			target.player_sprite.setPosition(tile.hitboxes[index].get_position().x - target.get_hitbox()->get_size().x + target.player_sprite.getGlobalBounds().width / 2, target.get_position().y - 1);
		}
			
		//if player is touching left wall
		if (check_direction(target, tile.hitboxes[index]) == "Left") {
			//move player right till it appears he is at right of the wall
			target.player_sprite.setPosition(tile.hitboxes[index].get_position().x + tile.hitboxes[index].get_size().x + target.player_sprite.getGlobalBounds().width / 2, target.get_position().y - 1);
		}
			
	}

}