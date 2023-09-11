#include "Level.hpp"

void Level::create(std::string level_input_path, std::string TileSet, sf::Vector2u tile_size, sf::Vector2u Tile_Texture_Size) {

	//tells the class what the size of the tiles are
	this->texture_size = Tile_Texture_Size;

	//centers the view
	this->camera.setCenter(sf::Vector2f(1366 / 2, 768 / 2));

	//sets the size of the view
	this->camera.setSize(sf::Vector2f(1366, 768));

	//loads the input file
	this->sample.loadFromFile("assets/levels/" + level_input_path);
	this->map.loadFromFile("assets/TileSet/" + TileSet);

	this->level_array.setPrimitiveType(sf::Quads);

	//Area of map (unit: tiles) * 4 points (of each tile)
	this->level_array.resize(LEVEL_WIDTH * LEVEL_HEIGHT * 4);

	for (int i = 0; i < LEVEL_HEIGHT; i++) {
		for (int j = 0; j < LEVEL_WIDTH; j++) {

			//defining the tiles array
			this->populate(sample.getPixel(j, i), j, i);

		}

	}

	for (int i = 0; i < LEVEL_HEIGHT; i++) {

		for (int j = 0; j < LEVEL_WIDTH; j++) {

			//populating the vertex array
			int current_tile = type[j][i];

			//gets vertices
			sf::Vertex* corners = &level_array[(j + i * tile_size.x) * 4];
			
			//defines position on screen of current quad
			corners[0].position = sf::Vector2f((j * tile_size.x), (i * tile_size.y));
			corners[1].position = sf::Vector2f((j * tile_size.x) + tile_size.x, (i * tile_size.y));
			corners[2].position = sf::Vector2f((j * tile_size.x) + tile_size.x, (i * tile_size.y) + tile_size.y);
			corners[3].position = sf::Vector2f((j * tile_size.x), (i * tile_size.y) + tile_size.y);

			//current tile starts from 1 to 17
			int y_offset = Tile_Texture_Size.y * (current_tile / (map.getSize().x / Tile_Texture_Size.x));
			int x_offset = Tile_Texture_Size.x * (current_tile % ((map.getSize().x / Tile_Texture_Size.x)));

			corners[0].texCoords = sf::Vector2f(x_offset, y_offset);
			corners[1].texCoords = sf::Vector2f(x_offset + Tile_Texture_Size.x, y_offset);
			corners[2].texCoords = sf::Vector2f(x_offset + Tile_Texture_Size.x, y_offset + Tile_Texture_Size.y);
			corners[3].texCoords = sf::Vector2f(x_offset, y_offset + Tile_Texture_Size.y);

		}

	}

}

void Level::create_hitboxes(sf::Vector2u tile_size) {

	for (int i = 0; i < LEVEL_HEIGHT; i++) {

		for (int j = 0; j < LEVEL_WIDTH; j++) {

			//checks through the whole array of block definitions
			for (int z = 0; z < NO_OF_PHYSICAL_BLOCKS; z++) {

				if(type[j][i] == get_tile_at(this->blocks.Physical_boxes[z][0], this->blocks.Physical_boxes[z][1]))
					this->hitboxes.push_back(Hitbox(sf::Vector2f(j * tile_size.x, i * tile_size.y), sf::Vector2f(tile_size.x, tile_size.y)));

			}

		}

	}

}

int Level::get_tile_at(int x, int y) {

	int width = map.getSize().x / this->texture_size.x;

	int result = (x - 1) + ((y - 1) * width);

	return result;
}

void Level::populate(sf::Color target, int x, int y) {

	for (int i = 0; i < NO_OF_BLOCKS; i++) {

		if (target == blocks.arr[i])
			this->type[x][y] = get_tile_at(blocks.Position[i][0], blocks.Position[i][1]);

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
	float pos = target.get_position().x - this->camera.getCenter().x + (target_window.getSize().x / 2.0f);

	//keep scrolling if the player is not dead or idle
	if (target.current_state != Player::Dead && target.current_state != Player::Idle) {

		if (target.current_direction == Player::L && pos < (target_window.getSize().x / 4.0f)) {
			this->camera.move(sf::Vector2f(-target.speed, 0));
		}

		else if (target.current_direction == Player::R && (3 * target_window.getSize().x / 4.0f) < pos) {
			this->camera.move(sf::Vector2f(target.speed, 0));
		}

	}

	sf::View current_window_view = target_window.getView();

	this->camera.setViewport(current_window_view.getViewport());

}

void Level::render(sf::RenderWindow& target_window) {

	target_window.setView(this->camera);

	target_window.draw(this->level_array, &map);

}