#include "Level.hpp"

void Level::create(std::string path, sf::Vector2u tile_size, sf::Vector2u Tile_Texture_Size) {

	//loads the input file
	this->sample.loadFromFile("assets/levels/" + path);
	this->map.loadFromFile("assets/TileSet/map.png");

	this->level_array.setPrimitiveType(sf::Quads);

	//Area of map (unit: tiles) * 4 points (of each tile)
	this->level_array.resize(level_width * level_height * 4);

	for (int i = 0; i < level_height; i++) {
		for (int j = 0; j < level_width; j++) {

			//defining the tiles array
			this->populate(sample.getPixel(j, i), i, j);

		}

	}

	int current_position = 0;

	for (int i = 0; i < level_height; i++) {

		for (int j = 0; j < level_width; j++) {

			//populating the vertex array
			int current_tile = type[i][j];

			//gets vertices
			sf::Vertex* corners = &level_array[current_position * 4];

			//defines position on screen of current quad
			corners[0].position = sf::Vector2f((j * tile_size.x), (i * tile_size.y));
			corners[1].position = sf::Vector2f((j * tile_size.x) + tile_size.x, (i * tile_size.y));
			corners[2].position = sf::Vector2f((j * tile_size.x) + tile_size.x, (i * tile_size.y) + tile_size.y);
			corners[3].position = sf::Vector2f((j * tile_size.x), (i * tile_size.y) + tile_size.y);

			int y_offset = Tile_Texture_Size.y * (current_tile / ((map.getSize().x / Tile_Texture_Size.y) + 1));
			int x_offset = Tile_Texture_Size.x * (current_tile % (map.getSize().x / Tile_Texture_Size.x));

			corners[0].texCoords = sf::Vector2f(x_offset, y_offset);
			corners[1].texCoords = sf::Vector2f(x_offset + Tile_Texture_Size.x, y_offset);
			corners[2].texCoords = sf::Vector2f(x_offset + Tile_Texture_Size.x, y_offset + Tile_Texture_Size.y);
			corners[3].texCoords = sf::Vector2f(x_offset, y_offset + Tile_Texture_Size.y);

			current_position++;

		}

	}

}

void Level::create_hitboxes(sf::Vector2u tile_size) {

	for (int i = 0; i < level_height; i++) {

		for (int j = 0; j < level_width; j++) {

			if (type[i][j] == get_tile_at(4, 14)) {
				this->hitboxes.push_back(Hitbox(sf::Vector2f(j * tile_size.x, i * tile_size.y), sf::Vector2f(tile_size.x, tile_size.y)));
			}

		}

	}

}

int Level::get_tile_at(int x, int y) {

	int width = map.getSize().x / this->texture_size.x;

	int result = x + ((y * width)) - 1;

	return result;
}

void Level::populate(sf::Color target, int x, int y) {

	if (target.r == 0 && target.g == 0 && target.b == 255) {

		//sky
		this->type[x][y] = get_tile_at(4, 12);

	}

	else if (target.r == 185 && target.g == 122 && target.b == 87) {

		//ground
		this->type[x][y] = get_tile_at(4, 14);

	}

}

sf::Vector2u Level::get_texture_size() {
	return this->texture_size;
}

void Level::set_texture_size(sf::Vector2u size) {
	this->texture_size = size;
}

void Level::render(sf::RenderWindow& target_window) {

	target_window.draw(this->level_array, &map);

}