#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>

#include "Hitbox.hpp"
#include "Player.hpp"

#define LEVEL_WIDTH 72
#define LEVEL_HEIGHT 12		//in pixels

class Level{

private:

	//default texture_size is 16x16
	sf::Vector2u texture_size = { 16, 16 };

public:

	sf::View camera;

	sf::VertexArray level_array;

	sf::Image sample;
	sf::Texture map;

	int type[LEVEL_WIDTH][LEVEL_HEIGHT];

	Level() {};

	std::vector<Hitbox> hitboxes;

	void create_hitboxes(sf::Vector2u tile_size);

	void create(std::string level_input_path, std::string TileSet, sf::Vector2u tile_size, sf::Vector2u Tile_Texture_Size);

	void populate(sf::Color target, int x, int y);

	void update(Player& target, sf::RenderWindow& target_window);

	void render(sf::RenderWindow& target_window);

	int get_tile_at(int x, int y);

	sf::Vector2u get_texture_size();

	void set_texture_size(sf::Vector2u size);
};