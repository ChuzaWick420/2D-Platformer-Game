#pragma once

#include <SFML/Graphics.hpp>

class Hitbox {

private:
	sf::Vector2f position;
	sf::Vector2f size;
	sf::RectangleShape hitbox;

public:

	Hitbox(sf::Vector2f t_position, sf::Vector2f t_size);

	void update(sf::Sprite target);

	bool collides(Hitbox target);

	sf::Vector2f get_position();

	sf::Vector2f get_size();

};