#include "Player.hpp"

Player::Player() {

	for (int i = 0; i < 10; i++) {

		walk_t[i].loadFromFile("../assets/Player/Walk (" + std::to_string(i + 1) + ").png");
		idle_t[i].loadFromFile("../assets/Player/Idle (" + std::to_string(i + 1) + ").png");
		jump_t[i].loadFromFile("../assets/Player/Jump (" + std::to_string(i + 1) + ").png");
		dead_t[i].loadFromFile("../assets/Player/Dead (" + std::to_string(i + 1) + ").png");

	}

	//sets up default texture
	this->player_sprite.setTexture(this->idle_t[0]);
	this->player_sprite.setScale(this->scale, this->scale);

	this->current_state = Player::Fall;

}

sf::Vector2f Player::get_position() {
	this->position = this->player_sprite.getPosition();
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

	case Player::Fall:
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

}

void Player::create_hitbox(sf::Vector2f t_position, sf::Vector2f t_size) {

	//player's origin is in the middle of the sprite

	this->hitbox.create(t_position, t_size);

}

void Player::set_position(sf::Vector2f t_position) {
	this->position = t_position;
}

void Player::jump(float gravity) {
	
	//if player's vertical velocity looses against gravity's strength then player is falling
	if (jump_velocity < 0)
		this->current_state = Player::Fall;

	//otherwise he is jumping but loosing his speed
	else
		//keeps subtracting a gravity value from jump velocity
		this->jump_velocity = this->jump_velocity - 0.02f;

	//then moving the player with net velocity
	this->player_sprite.move(0, -jump_velocity);

}

Hitbox* Player::get_hitbox() {

	return &this->hitbox;

}

float Player::get_jump_velocity() {
	return this->jump_velocity;
}

void Player::set_jump_velocity(float value) {
	this->jump_velocity = value;
}