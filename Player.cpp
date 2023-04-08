#include "Player.hpp"

Player::Player() {

	for (int i = 0; i < 10; i++) {

		walk_t[i].loadFromFile("assets/Player/Walk (" + std::to_string(i + 1) + ").png");
		idle_t[i].loadFromFile("assets/Player/Idle (" + std::to_string(i + 1) + ").png");
		jump_t[i].loadFromFile("assets/Player/Jump (" + std::to_string(i + 1) + ").png");
		dead_t[i].loadFromFile("assets/Player/Dead (" + std::to_string(i + 1) + ").png");

	}

	//sets up default texture
	this->player_sprite.setTexture(this->idle_t[0]);
	this->player_sprite.setScale(this->scale, this->scale);

}

sf::Vector2f Player::get_position() {
	return this->position;
}

void Player::render(sf::RenderWindow& target_window) {

	target_window.draw(this->player_sprite);

}

void Player::animate(state is_doing, int frame_number) {

	switch (is_doing){

	case Player::Dead:
		this->player_sprite.setTexture(this->dead_t[frame_number]);
		break;

	case Player::Idle:
		this->player_sprite.setTexture(this->idle_t[frame_number]);
		break;

	case Player::Walk:
		this->player_sprite.setTexture(this->walk_t[frame_number]);
		break;

	case Player::Jump:
		this->player_sprite.setTexture(this->jump_t[frame_number]);
		break;

	default:
		break;

	}

	//resize the character in the end depending on direction
	if (this->current_direction == Player::direction::R)
		this->player_sprite.setScale(this->scale, this->scale);

	if (this->current_direction == Player::direction::L)
		this->player_sprite.setScale(-this->scale, this->scale);

	//updates hitbox
	this->hitbox.update(this->player_sprite);

}

void Player::create_hitbox(sf::Vector2f t_position, sf::Vector2f t_size) {

	this->hitbox.create(t_position, t_size);

}

void Player::set_position(sf::Vector2f t_position) {
	this->position = t_position;
}

void Player::jump() {

	

}

Hitbox Player::get_hitbox() {

	return this->hitbox;

}