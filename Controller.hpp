#pragma once

#include <SFML/Graphics.hpp>

#include "Player.hpp"

void control(Player& target) {

	//check if player is pressing or released both keys
	bool L_and_R = 
		( sf::Keyboard::isKeyPressed(sf::Keyboard::A) && 
		  sf::Keyboard::isKeyPressed(sf::Keyboard::D) ) 
		|| 
		!( sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
		   sf::Keyboard::isKeyPressed(sf::Keyboard::D) );

	//checks if player is pressing either of the keys
	bool L_or_R = sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D);

	//left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::D))) {
		target.current_direction = Player::L;
		target.player_sprite.move(-target.speed, 0);
	}

	//right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::A))) {
		target.current_direction = Player::R;
		target.player_sprite.move(target.speed, 0);
	}

	//if player is pressing either of the buttons
	if (L_or_R == true) {

		//check if he is on ground
		if (target.on_ground == true)
			//then
			target.current_state = Player::Walk;

		//otherwise
		else {

			if (target.is_jumping == true)
				target.current_state = Player::Jump;

			else
				target.current_state = Player::Fall;

		}
	}

	//idle
	if (L_and_R == true && target.on_ground == true)
		target.current_state = Player::Idle;

	//jump
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && target.on_ground == true) {
		target.current_state = Player::Jump;
		target.on_ground = false;
		target.is_jumping = true;
	}

	if (target.current_state == Player::Jump) {
		target.jump(target.get_jump_velocity());
	}

	//debug area
	//down
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		target.player_sprite.move(0, 1);
	}

	//up
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		target.player_sprite.move(0, -1);
	}

}