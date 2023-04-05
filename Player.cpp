#include "Player.hpp"

Player::Player() {

	for (int i = 0; i < 10; i++) {

		walk_t[i].loadFromFile("assets/Player/Walk (" + std::to_string(i + 1) + ").png");
		idle_t[i].loadFromFile("assets/Player/Idle (" + std::to_string(i + 1) + ").png");
		jump_t[i].loadFromFile("assets/Player/Jump (" + std::to_string(i + 1) + ").png");
		dead_t[i].loadFromFile("assets/Player/Dead (" + std::to_string(i + 1) + ").png");

	}

}

void Player::render(sf::RenderWindow& target_window) {

	target_window.draw(player_current);

}

void Player::animate(state is_doing, int frame_number) {

	switch (is_doing){

	case Player::Dead:
		this->player_current.setTexture(this->dead_t[frame_number]);
		break;

	case Player::Idle:
		this->player_current.setTexture(this->idle_t[frame_number]);
		break;

	case Player::Walk:
		this->player_current.setTexture(this->walk_t[frame_number]);
		break;

	case Player::Jump:
		this->player_current.setTexture(this->jump_t[frame_number]);
		break;

	default:
		break;

	}

	//resize the character in the end depending on direction
	if (this->current_direction == Player::direction::R)
		this->player_current.setScale(this->scale, this->scale);

	if (this->current_direction == Player::direction::L)
		this->player_current.setScale(-this->scale, this->scale);

}

void Player::jump() {



}