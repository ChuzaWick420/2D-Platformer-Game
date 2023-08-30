#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>

#include "/Hitbox.hpp"
#include "/Player.hpp"

#define LEVEL_WIDTH 72
#define LEVEL_HEIGHT 12		//in pixels

#define NO_OF_BLOCKS 19
#define NO_OF_PHYSICAL_BLOCKS 14

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

	struct Block_pieces {

		sf::Color arr[NO_OF_BLOCKS] = {
			{0, 0, 255},
			{34, 177, 76},
			{34, 176, 76},
			{34, 178, 76},
			{34, 177, 75},
			{34, 176, 75},
			{34, 178, 75},
			{185, 122, 87},
			{185, 121, 87},
			{185, 123, 87},
			{185, 122, 86},
			{185, 121, 86},
			{185, 123, 86},
			{186, 121, 87},
			{186, 122, 87},
			{186, 123, 87},
			{181, 230, 28},
			{181, 230, 29},
			{181, 230, 30}
		};

		int Position[NO_OF_BLOCKS][2] = {
			{4, 12},
			{14, 1},
			{13, 1},
			{15, 1},
			{14, 2},
			{13, 2},
			{15, 2},
			{2, 1},
			{1, 1},
			{3, 1},
			{2, 2},
			{1, 2},
			{3, 2},
			{13, 3},
			{14, 3},
			{15, 3},
			{13, 4},
			{14, 4},
			{15, 4}
		};

		int Physical_boxes[NO_OF_PHYSICAL_BLOCKS][2] = {
			{4, 14},
			{14, 1},
			{13, 1},
			{1, 2},
			{3, 2},
			{13, 3},
			{14, 3},
			{15, 3},
			{13, 2},
			{14, 2},
			{15, 2},
			{13, 4},
			{14, 4},
			{15, 4}
		};

	};

	Block_pieces blocks;

};