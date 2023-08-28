#include "GUI.hpp"

void GUI::init() {

	//loads the main menu
	m_menu_t.loadFromFile("assets/GUI/mainmenu.jpg");

	//sets the texture to the sprite
	m_menu_s.setTexture(m_menu_t);

	//sets current displayed screen to the main menu
	Current_Screen = m_menu_s;
	current_state = main_menu;

	//loads the play button
	Play.create("Play");

}

void GUI::render(sf::RenderWindow& target_window) {
	//draws the current screen
	target_window.draw(this->Current_Screen);

	if (this->current_state == main_menu)
		target_window.draw(*Play.get_sprite());

	if (this->current_state == level_selector) {

		for (int i = 0; i < LEVELS; i++)
			target_window.draw(*levels[i].Level.get_sprite());
	}

}

void GUI::resize(sf::RenderWindow& t_window) {

	//16:9
	sf::Vector2f scale = { -1, -1};

	if (t_window.getSize().x / t_window.getSize().y <= 16.0f / 9.0f) {
		scale = {
			/*width  scale = */ (float)t_window.getSize().x / m_menu_t.getSize().x,
			/*height scale = */ (float)(t_window.getSize().x / 16 * 9) / m_menu_t.getSize().y
		};
	}
	else {
		scale = {
			/*width  scale = */ (float)(t_window.getSize().y / 9 * 16) / m_menu_t.getSize().x,
			/*height scale = */ (float)t_window.getSize().y / m_menu_t.getSize().y
		};
	}

	//gets the size of the window and resizes the current screen to fit it
	this->m_menu_s.setScale(scale);

	this->Current_Screen = m_menu_s;
	this->Current_Screen.setScale(scale);

	float horizontal_offset = m_menu_t.getSize().x * scale.x / 2.0f;
	float vertical_offset   = m_menu_t.getSize().y * scale.y / 2.0f;

	//initialize the play button once the screen is resized
	this->Play.initialize(sf::Vector2f(horizontal_offset, vertical_offset), sf::Vector2f(2, 2));

}

void GUI::animate(int frame_number) {

}

void GUI::construct_screen(std::string type) {

	if (type == "level_selector") {

		//loads the level selector
		this->level_selector_t.loadFromFile("assets/GUI/level_selector.png");

		//sets the texture of level selector to the sprite
		this->level_selector_s.setTexture(this->level_selector_t);

		//creates the level buttons
		for (int i = 0; i < LEVELS; i++) {
			levels[i].Level.create("Level_Selector");
		}

	}

}

void GUI::transition(sf::Vector2u screen_resolution) {

	//changes the current screen according to what is happening on screen
	if (this->Play.triggered == true) {

		this->construct_screen("level_selector");

		this->Current_Screen = level_selector_s;
		this->current_state = level_selector;

		//spawns the level buttons equality distant

		sf::Vector2f spacing = {
			(float (screen_resolution.x) / (2 * LEVELS_PER_ROW - 1 + 2)),
			(float (screen_resolution.y) / (2 * LEVELS_PER_COLUMN - 1 + 2))
		};

		for (int i = 0; i < LEVELS_PER_ROW; i++) {
			for (int j = 0; j < LEVELS_PER_COLUMN; j++) {

				//translate 2d to 1d
				int index = j * LEVELS_PER_ROW + i;

				//sets the position of the level buttons
				levels[index].Level.initialize(sf::Vector2f(
					(2 * i + 1) * spacing.x + levels[index].Level.get_sprite()->getOrigin().x * levels[index].Level.get_sprite()->getScale().x,
					(2 * j + 1) * spacing.y + levels[index].Level.get_sprite()->getOrigin().y
				), sf::Vector2f(1.3, 1.3));
			}
		}

		levels[0].unlocked = true;

		//once transiton has be done, reset the trigger
		this->Play.triggered = false;

	}

	if (current_state == level_selector) {

		for (int i = 0; i < LEVELS_PER_ROW; i++) {
			for (int j = 0; j < LEVELS_PER_COLUMN; j++) {
				//translate 2d to 1d
				int index = j * LEVELS_PER_ROW + i;

				if (levels[index].Level.triggered == true && levels[index].unlocked == true) {

					//since we just want the level selector to just disappear, so we set an empty texture/sprite
					this->Current_Screen = level_screen_s;
					this->current_state = level_screen;

					//once transiton has be done, reset the trigger
					levels[index].Level.triggered = false;
				}

			}
		}

	}

}