#pragma once
#include <iostream>

#include <SFML/Graphics.hpp>

#include "Player.hpp"
#include "Hitbox.hpp"

void control(Player& target) {

	//left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::D))) {

		target.current_state = Player::Walk;
		target.current_direction = Player::L;
		target.player_sprite.move(-target.speed, 0);
	}

	//right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::A))) {

		target.current_state = Player::Walk;
		target.current_direction = Player::R;
		target.player_sprite.move(target.speed, 0);
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
	
		std::cout << "(" << target.player_sprite.getPosition().x << ", " << target.player_sprite.getPosition().y << ")" << std::endl;
	
	}

}

void apply_gravity(sf::Sprite& target, Hitbox hitbox, float& gravity_val, bool& on_ground) {

	//difference between feet of player and bottom of sprite
	float offset = 10;

	if ((target.getGlobalBounds().height/2 + target.getPosition().y - offset) < hitbox.get_position().y && on_ground == false) {

		gravity_val += 0.01;

		target.move(0, gravity_val);

	}

	else if ((target.getGlobalBounds().height/2 + target.getPosition().y - offset) >= hitbox.get_position().y && on_ground == false) {
		target.setPosition(target.getPosition().x, hitbox.get_position().y - target.getGlobalBounds().height/2 + offset);
		on_ground = true;
		gravity_val = 0;
	}

}