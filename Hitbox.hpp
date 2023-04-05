#pragma once

#include <SFML/Graphics.hpp>

struct Hitbox{

	sf::Vector2f corner;

	enum Type {
		ground
	};

	Type box_type;

};