#include "Level.hpp"

void Level::create(std::string level_input_path, std::string TileSet, sf::Vector2u tile_size, sf::Vector2u Tile_Texture_Size) {

	//tells the class what the size of the tiles are
	this->texture_size = Tile_Texture_Size;

	//centers the view
	this->camera.setCenter(sf::Vector2f(1368 / 2, 768 / 2));

	//sets the size of the view
	this->camera.setSize(sf::Vector2f(1368, 768));

	//loads the input file
	this->sample.loadFromFile("assets/levels/" + level_input_path);
	this->map.loadFromFile("assets/TileSet/" + TileSet);

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

			int y_offset = Tile_Texture_Size.y * (current_tile / ((map.getSize().x / Tile_Texture_Size.x) + 1));
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

			//types of tiles that will have hitboxes
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

	else if (target.r == 0 && target.g == 255 && target.b == 0) {

		//bush
		this->type[x][y] = get_tile_at(1, 1);

	}

}

sf::Vector2u Level::get_texture_size() {
	return this->texture_size;
}

void Level::set_texture_size(sf::Vector2u size) {
	this->texture_size = size;
}

void Level::update(Player& target, sf::RenderWindow& target_window) {

	//Position of player relative to the Left side of the window
	float pos = target.get_position().x - this->camera.getCenter().x + (target_window.getSize().x / 2);

	//scroll if pos is less than 1/4 of the window or more than 3/4 of the window
	if (pos < (target_window.getSize().x / 4) || (3 * target_window.getSize().x / 4) < pos) {

		//keep scrolling if the player is not dead or idle
		if (target.current_state != Player::Dead && target.current_state != Player::Idle) {

			if (target.current_direction == Player::L) {
				this->camera.move(sf::Vector2f(-target.speed, 0));
			}

			else if (target.current_direction == Player::R) {
				this->camera.move(sf::Vector2f(target.speed, 0));
			}
		}

	}

}

void Level::render(sf::RenderWindow& target_window) {

	target_window.setView(this->camera);

	target_window.draw(this->level_array, &map);

}