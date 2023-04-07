#include "Hitbox.hpp"

Hitbox::Hitbox(sf::Vector2f t_position, sf::Vector2f t_size) {

	this->position = t_position;
	this->size = t_size;
	this->hitbox.setPosition(t_position);
	this->hitbox.setSize(t_size);
	this->hitbox.setFillColor(sf::Color::Transparent);
	
}

void Hitbox::update(sf::Sprite target) {

	this->hitbox.setPosition(target.getPosition());

}

bool Hitbox::collides(Hitbox target) {

	if (this->hitbox.getGlobalBounds().intersects(target.hitbox.getGlobalBounds())) {
		return true;
	}

	return false;
}

sf::Vector2f Hitbox::get_position() {

	return this->position;

}

sf::Vector2f Hitbox::get_size() {

	return this->size;

}