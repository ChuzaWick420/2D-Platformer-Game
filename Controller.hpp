#pragma once

#include <SFML/Graphics.hpp>

#include "Player.hpp"

void control(Player& target) {

	//left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::D))) {

		if(target.on_ground == true)
			target.current_state = Player::Walk;
		else
			target.current_state = Player::Jump;

		target.current_direction = Player::L;
		target.player_sprite.move(-target.speed, 0);
	}

	//right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::A))) {

		if (target.on_ground == true)
			target.current_state = Player::Walk;
		else
			target.current_state = Player::Jump;

		target.current_direction = Player::R;
		target.player_sprite.move(target.speed, 0);
	}

	//idle
	if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::D) || (sf::Keyboard::isKeyPressed(sf::Keyboard::A))) && target.on_ground == true) {
		target.current_state = Player::Idle;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && (sf::Keyboard::isKeyPressed(sf::Keyboard::A))) {
		target.current_state = Player::Idle;
	}

	//jump
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && target.on_ground == true) {
		target.current_state = Player::Jump;
		target.on_ground = false;
	}

	if (target.on_ground == false) {
		target.jump(target.get_jump_force());
	}

}