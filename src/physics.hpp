#pragma once

#include <iostream>
#include <string>
#include <cmath>

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

void collision_correction(Player* T, Level& collider) {
	
	bool check = false;

	//gets the collision map
	std::vector<int> checker_array = check_collision(*T, collider);

	sf::Vector2f allowed_overlap = { 10, 10 };

	int t_hit_top = 0;
	int t_hit_bottom = 0;
	int t_hit_right = 0;
	int t_hit_left = 0;

	int c_hit_top = 0;
	int c_hit_bottom = 0;
	int c_hit_right = 0;
	int c_hit_left = 0;

	for (std::vector<int>::iterator i = checker_array.begin(); i != checker_array.end(); i++) {

		//if there was a collision, i will be 1 instead of -1
		if (*i == 1) {

			//corner coordinates
			sf::Vector2f P_Pos = (*T).get_hitbox()->get_position();
			sf::Vector2f P_Size = (*T).get_hitbox()->get_size();

			sf::Vector2f C_Pos = collider.hitboxes[i - checker_array.begin()].get_position();
			sf::Vector2f C_Size = collider.hitboxes[i - checker_array.begin()].get_size();

			t_hit_top = P_Pos.y;
			t_hit_bottom = P_Pos.y + P_Size.y;
			t_hit_right = P_Pos.x + P_Size.x;
			t_hit_left = P_Pos.x;

			c_hit_top = C_Pos.y;
			c_hit_bottom = C_Pos.y + C_Size.y;
			c_hit_right = C_Pos.x + C_Size.x;
			c_hit_left = C_Pos.x;

			//collision from right
			if (t_hit_right >= c_hit_left 
				&& abs(t_hit_right - c_hit_left) <= allowed_overlap.x
				&& abs(t_hit_bottom - c_hit_top) >= allowed_overlap.y
			) {

				//fixes position
				T->player_sprite.setPosition(sf::Vector2f(c_hit_left - 1 - P_Size.x / 2, T->player_sprite.getPosition().y));

				if (!(abs(c_hit_left - t_hit_right) > allowed_overlap.x && abs(c_hit_right - t_hit_left) > allowed_overlap.x))
					check = true;
			}

			//collision from left
			if (c_hit_right >= t_hit_left
				&& abs(t_hit_left - c_hit_right) <= allowed_overlap.x
				&& abs(t_hit_bottom - c_hit_top) >= allowed_overlap.y
			) {

				//fixes position
				T->player_sprite.setPosition(sf::Vector2f(c_hit_right + 1 + P_Size.x / 2, T->player_sprite.getPosition().y));
				if (!(abs(c_hit_left - t_hit_right) > allowed_overlap.x && abs(c_hit_right - t_hit_left) > allowed_overlap.x))
					check = true;
			}

			if (abs(c_hit_left - t_hit_right) > allowed_overlap.x && abs(c_hit_right - t_hit_left) > allowed_overlap.x) {

				//collision from top
				if (t_hit_top <= c_hit_bottom && abs(t_hit_top - c_hit_bottom) <= allowed_overlap.y) {

					//fixes position
					T->current_state = Player::Fall;
					T->on_ground = false;
					T->is_jumping = false;

				}

				//collision from bottom
				if (t_hit_bottom > c_hit_top && abs(t_hit_bottom - c_hit_top) <= allowed_overlap.y && (*T).current_state == Player::Fall) {

					//fixes position
					T->current_state = Player::Idle;
					T->is_jumping = false;
					T->on_ground = true;

					//reset vertical velocity
					T->set_jump_velocity(3);

				}

				check = true;
			}

		}

	}

	if (check == false)
		T->on_ground = false;

}

void apply_gravity(Player& target, Level& tile, float& gravity_val) {

	if (target.on_ground == false) {

		if (target.current_state == Player::Fall) {
			gravity_val += 0.02f;
			target.player_sprite.move(0, gravity_val);
		}

	}

	else
		gravity_val = 0;

}