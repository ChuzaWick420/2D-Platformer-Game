#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>

#include "Hitbox.hpp"

#define level_width 72
#define level_height 12		//in pixels

class Level{

private:

	//default texture_size is 16x16
	sf::Vector2u texture_size = { 16, 16 };

public:

	sf::View camera;

	sf::VertexArray level_array;

	sf::Image sample;
	sf::Texture map;

	int type[level_height][level_width];

	Level() {};

	std::vector<Hitbox> hitboxes;

	void create_hitboxes(sf::Vector2u tile_size);

	void create(std::string level_input_path, std::string TileSet, sf::Vector2u tile_size, sf::Vector2u Tile_Texture_Size);

	void populate(sf::Color target, int x, int y);

	void render(sf::RenderWindow& target_window);

	int get_tile_at(int x, int y);

	sf::Vector2u get_texture_size();

	void set_texture_size(sf::Vector2u size);
};