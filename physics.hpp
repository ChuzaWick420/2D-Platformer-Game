#pragma once
#include <iostream>

#include <SFML/Graphics.hpp>

#include "Player.hpp"
#include "Hitbox.hpp"

void apply_gravity(Player& target, Hitbox hitbox, float& gravity_val, bool& on_ground) {

	//difference between feet of player and bottom of sprite
	float offset = 10;

	if ((target.player_sprite.getGlobalBounds().height/2 + target.player_sprite.getPosition().y - offset) < hitbox.get_position().y && on_ground == false) {

		gravity_val += 0.01;

		target.set_jump_force(target.get_jump_force() - 0.01);

		target.player_sprite.move(0, gravity_val);

	}

	//reset
	else if ((target.player_sprite.getGlobalBounds().height/2 + target.player_sprite.getPosition().y - offset) >= hitbox.get_position().y) {

		target.player_sprite.setPosition(target.player_sprite.getPosition().x, hitbox.get_position().y - target.player_sprite.getGlobalBounds().height/2 + offset);
		target.set_jump_force(3);
		on_ground = true;
		gravity_val = 0;

	}

}