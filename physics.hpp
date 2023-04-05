#pragma once
#include <iostream>

#include <SFML/Graphics.hpp>

#include "Player.hpp"

bool control(Player& target) {

	bool trigger = false;

	//left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::D))) {

		if (target.current_direction == Player::R)
			trigger = true;

		target.current_state = Player::Walk;
		target.current_direction = Player::L;
		target.player_current.move(-target.speed, 0);
	}

	//right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::A))) {

		if (target.current_direction == Player::L)
			trigger = true;

		target.current_state = Player::Walk;
		target.current_direction = Player::R;
		target.player_current.move(target.speed, 0);
	}

	//idle
	if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::D) || (sf::Keyboard::isKeyPressed(sf::Keyboard::A))) && target.on_ground == true) {
		target.current_state = Player::Idle;
	}

	//jump
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		target.current_state = Player::Jump;
		target.on_ground = false;
	}

	//debugging
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
	
		std::cout << "(" << target.player_current.getPosition().x << ", " << target.player_current.getPosition().y << ")" << std::endl;
	
	}

	return trigger;

}