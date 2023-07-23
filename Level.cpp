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

			//types of tiles that will have hitboxes
			if (
				type[j][i] == get_tile_at(4, 14) || 
				type[j][i] == get_tile_at(14, 1) ||
				type[j][i] == get_tile_at(13, 1) ||
				type[j][i] == get_tile_at(15, 1) ||
				type[j][i] == get_tile_at(1, 2) ||
				type[j][i] == get_tile_at(3, 2)
			)
				this->hitboxes.push_back(Hitbox(sf::Vector2f(j * tile_size.x, i * tile_size.y), sf::Vector2f(tile_size.x, tile_size.y)));
			
		}

	}

}

int Level::get_tile_at(int x, int y) {

	int width = map.getSize().x / this->texture_size.x;

	int result = (x - 1) + ((y - 1) * width);

	return result;
}

void Level::populate(sf::Color target, int x, int y) {

	if (target == sf::Color(0, 0, 255))
		//sky
		this->type[x][y] = get_tile_at(4, 12);

	else if (target == sf::Color(34, 177, 76))
		//ground grass mid
		this->type[x][y] = get_tile_at(14, 1);

	else if (target == sf::Color(34, 176, 76))
		//ground grass left
		this->type[x][y] = get_tile_at(13, 1);

	else if (target == sf::Color(34, 178, 76))
		//ground grass right
		this->type[x][y] = get_tile_at(15, 1);

	else if (target == sf::Color(34, 177, 75))
		//ground grass lower mid
		this->type[x][y] = get_tile_at(14, 2);

	else if (target == sf::Color(185, 122, 87))
		//Platform_top_mid
		this->type[x][y] = get_tile_at(2, 1);

	else if (target == sf::Color(185, 121, 87))
		//Platform_top_left
		this->type[x][y] = get_tile_at(1, 1);

	else if (target == sf::Color(185, 123, 87))
		//Platform_top_right
		this->type[x][y] = get_tile_at(3, 1);

	else if (target == sf::Color(185, 122, 86))
		//Platform_lower_mid
		this->type[x][y] = get_tile_at(2, 2);

	else if (target == sf::Color(185, 121, 86))
		//Platform_lower_left
		this->type[x][y] = get_tile_at(1, 2);

	else if (target == sf::Color(185, 123, 86))
		//Platform_lower_right
		this->type[x][y] = get_tile_at(3, 2);

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