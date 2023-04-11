#pragma once
#include <iostream>

#include <SFML/Graphics.hpp>

#include "Player.hpp"
#include "Hitbox.hpp"
#include "Level.hpp"

void apply_gravity(Player& target, Level& tile, float& gravity_val, bool& on_ground) {

	//difference between feet of player and bottom of sprite
	float offset = 10;

	int index = -1;

	//iterates over all hitboxes in the level
	for (std::vector<Hitbox>::iterator i = tile.hitboxes.begin(); i != tile.hitboxes.end(); i++) {

		if (
			target.get_hitbox().get_position().x + target.get_hitbox().get_size().x > i->get_position().x &&
			target.get_hitbox().get_position().x < i->get_position().x + i->get_size().x
			) {
			index = i - tile.hitboxes.begin();
			break;
		}

	}

	if (target.get_hitbox().collides(tile.hitboxes[index]) == false) {
		on_ground = false;
	}

	if ((target.player_sprite.getGlobalBounds().height/2 + target.player_sprite.getPosition().y - offset) < tile.hitboxes[index].get_position().y && on_ground == false) {

		gravity_val += 0.01;

		if(target.current_state == Player::Jump)
			target.set_jump_force(target.get_jump_force() - 0.01);

		target.player_sprite.move(0, gravity_val);

	}

	//reset
	else if ((target.player_sprite.getGlobalBounds().height/2 + target.player_sprite.getPosition().y - offset) >= tile.hitboxes[index].get_position().y) {

		target.player_sprite.setPosition(target.player_sprite.getPosition().x, tile.hitboxes[index].get_position().y - target.player_sprite.getGlobalBounds().height/2 + offset);
		target.set_jump_force(3);
		on_ground = true;
		gravity_val = 0;

	}

	if (target.on_ground == true)
		target.is_jumping = false;

}