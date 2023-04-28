#pragma once

#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

#include "Player.hpp"
#include "Hitbox.hpp"
#include "Level.hpp"

//returns index of hitbox that player is colliding with
std::vector<int> check_collision(Player& target, Level& tile) {

	std::vector<int> collision_map = {-1};

	//iterates over all hitboxes in the level
	for (std::vector<Hitbox>::iterator i = tile.hitboxes.begin(); i != tile.hitboxes.end(); i++) {

		collision_map.push_back(-1);

		//if player is colliding with a hitbox
		if (target.get_hitbox()->collides(*i)) {
			
			collision_map[i - tile.hitboxes.begin()] = 1;
		}

		else{
			collision_map[i - tile.hitboxes.begin()] = -1;
		}

	}

	//return -1 if no collision
	return collision_map;

}

std::string check_direction(Player& target, Hitbox& collider) {

	//collider is at bottom
	if (target.get_hitbox()->get_position().y + target.get_hitbox()->get_size().y - collider.get_size().y / 2 < collider.get_position().y && target.get_hitbox()->get_position().y + target.get_hitbox()->get_size().y > collider.get_position().y)
		return "Bottom";

	//collider is at top
	if (target.get_hitbox()->get_position().y > collider.get_position().y + collider.get_size().y / 2 && target.get_hitbox()->get_position().y < collider.get_position().y + collider.get_size().y)
		return "Top";

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

	//debugging player state
	if (false) {
		switch (target.current_state) {
		case 0:
			std::cout << "Dead" << std::endl;
			break;

		case 1:
			std::cout << "Idle" << std::endl;
			break;

		case 2:
			std::cout << "Walk" << std::endl;
			break;

		case 3:
			std::cout << "Jump" << std::endl;
			break;

		case 4:
			std::cout << "Fall" << std::endl;
			break;

		default:
			std::cout << "Error!" << std::endl;
			break;
		}
	}

	//gets array of hitboxes that player is colliding with
	std::vector<int> checker_array = check_collision(target, tile);

	bool is_colliding = false;

	for (std::vector<int>::iterator index = checker_array.begin(); index != checker_array.end(); index++) {

		//if there is a collision
		if (*index == 1) {

			is_colliding = true;

			//if player is touching bottom of any tile
			if (check_direction(target, tile.hitboxes[index - checker_array.begin()]) == "Bottom" && target.current_state != Player::Jump) {

				gravity_val = 0;

				//move player up till it appears he is at top
				target.player_sprite.setPosition(target.get_position().x, tile.hitboxes[index - checker_array.begin()].get_position().y - target.player_sprite.getGlobalBounds().height / 2 + 10);

				//and anounce that he is on ground now
				target.on_ground = true;
				target.is_jumping = false;

				//reset vertical velocity
				target.set_jump_velocity(3);

			}

			else
				is_colliding = false;

			//if player is touching top of any tile
			if (check_direction(target, tile.hitboxes[index - checker_array.begin()]) == "Top") {
				//move player down till it appears he is at bottom
				target.player_sprite.setPosition(target.get_position().x, tile.hitboxes[index - checker_array.begin()].get_position().y + tile.hitboxes[index - checker_array.begin()].get_size().y + target.player_sprite.getGlobalBounds().height / 2);
				target.current_state = Player::Fall;
				target.is_jumping = false;
			}

			//if player is touching right wall
			if (check_direction(target, tile.hitboxes[index - checker_array.begin()]) == "Right") {
				//move player left till it appears he is at left of the wall
				target.player_sprite.setPosition(tile.hitboxes[index - checker_array.begin()].get_position().x - target.get_hitbox()->get_size().x + target.player_sprite.getGlobalBounds().width / 2 - 1, target.get_position().y);
			}

			//if player is touching left wall
			if (check_direction(target, tile.hitboxes[index - checker_array.begin()]) == "Left") {
				//move player right till it appears he is at right of the wall
				target.player_sprite.setPosition(tile.hitboxes[index - checker_array.begin()].get_position().x + tile.hitboxes[index - checker_array.begin()].get_size().x + target.player_sprite.getGlobalBounds().width / 2, target.get_position().y);
			}

		}

	}

	if (is_colliding == false) {

		target.on_ground = false;

		if (target.current_state == Player::Fall) {
			gravity_val += 0.02f;
			target.player_sprite.move(0, gravity_val);
		}

	}

}