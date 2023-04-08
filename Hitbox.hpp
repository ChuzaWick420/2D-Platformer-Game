#pragma once

#include <SFML/Graphics.hpp>

class Hitbox {

private:
	sf::Vector2f position;
	sf::Vector2f size;
	sf::RectangleShape hitbox;

public:

	Hitbox() {};

	//overloaded version of constructor
	Hitbox(sf::Vector2f t_position, sf::Vector2f t_size) { this->create(t_position, t_size); };

	void create(sf::Vector2f t_position, sf::Vector2f t_size);

	void update(sf::Sprite& target);

	bool collides(Hitbox& target);

	sf::Vector2f get_position();

	sf::Vector2f get_size();

	//debug area
	void render(sf::RenderWindow& target_window);

};