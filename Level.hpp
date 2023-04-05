#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>

#include "Hitbox.hpp"

#define level_width 72
#define level_height 12		//in pixels

class Level{

public:

	sf::View camera;

	sf::VertexArray level_array;

	sf::Image sample;
	sf::Texture map;

	int type[level_height][level_width];

	Hitbox box;

	Level(){}

	void create(std::string path, sf::Vector2u tile_size);

	void populate(sf::Color target, int x, int y);

	void render(sf::RenderWindow& target_window);

	int get_tile_at(int x, int y);
};