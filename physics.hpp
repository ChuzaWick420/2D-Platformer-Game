#pragma once

#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

#include "Player.hpp"
#include "Hitbox.hpp"
#include "Level.hpp"

//returns an array which represents which hitboxes the player is colliding with
std::vector<int> check_collision(Player& target, Level& tile) {

	std::vector<int> collision_map = {-1};

	//iterates over all hitboxes in the level
	for (std::vector<Hitbox>::iterator i = tile.hitboxes.begin(); i != tile.hitboxes.end(); i++) {

		//creates a new element in the collision map with every tile in the level
		collision_map.push_back(-1);

		//if player is colliding with a hitbox currently being checkked
		if (target.get_hitbox()->collides(*i)) {
			//set the collision map's corresponding element to 1
			collision_map[i - tile.hitboxes.begin()] = 1;
		}

		else{
			collision_map[i - tile.hitboxes.begin()] = -1;
		}

	}

	//return the collision map
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

	//gets the collision map
	std::vector<int> checker_array = check_collision(target, tile);

	//initially set on_ground to false
	target.on_ground = false;

	//if player touches the ground, set on_ground to true
	for (std::vector<int>::iterator index = checker_array.begin(); index != checker_array.end(); index++) {

		//if there is a collision
		if (*index == 1) {

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
				target.player_sprite.setPosition(tile.hitboxes[index - checker_array.begin()].get_position().x + tile.hitboxes[index - checker_array.begin()].get_size().x + target.player_sprite.getGlobalBounds().width / 2 + 1, target.get_position().y);
			}

		}

	}

	//after the whole loop, if there was no floor collision, on_ground will remain false

	if (target.on_ground == false) {

		if (target.current_state == Player::Fall) {
			gravity_val += 0.02f;
			target.player_sprite.move(0, gravity_val);
		}

	}

}