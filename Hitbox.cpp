#include "Hitbox.hpp"

void Hitbox::create(sf::Vector2f t_position, sf::Vector2f t_size) {

	this->position = t_position;
	this->size = t_size;
	this->hitbox.setPosition(t_position);
	this->hitbox.setSize(t_size);
	this->hitbox.setFillColor(sf::Color::Color(255, 0, 0, 128));	//debug
	
}

void Hitbox::update(sf::Sprite& target) {

	//updates the rectangle
	this->hitbox.setPosition(target.getPosition().x - target.getOrigin().x * abs(target.getScale().x), target.getPosition().y - target.getOrigin().y * abs(target.getScale().y));
	//then also its own position
	this->position = this->hitbox.getPosition();
}

bool Hitbox::collides(Hitbox& target) {

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

void Hitbox::render(sf::RenderWindow& target_window) { 

	target_window.draw(this->hitbox);

}