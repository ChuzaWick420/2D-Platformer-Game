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
	target_window.draw(Current_Screen);

	if (this->current_state == main_menu)
		target_window.draw(*Play.get_sprite());
	if (this->current_state == level_selector)
		for (int i = 0; i < LEVELS; i++)
			target_window.draw(*Levels[i].get_sprite());

}

void GUI::resize(sf::Vector2f size) {
	//gets the size of the window and resizes the current screen to fit it
	m_menu_s.setScale(size.x / Current_Screen.getGlobalBounds().width, size.y / Current_Screen.getGlobalBounds().height);

	Current_Screen = m_menu_s;
	current_state = main_menu;

	//initialize the play button once the screen is resized
	Play.initialize(sf::Vector2f(size.x / 2, size.y / 2), sf::Vector2f(2.5, 2.5));

}

void GUI::animate(int frame_number) {

}

void GUI::construct_screen(std::string type) {

	if (type == "level_selector") {

		//loads the level selector
		level_selector_t.loadFromFile("assets/GUI/level_selector.png");

		//sets the texture of level selector to the sprite
		level_selector_s.setTexture(level_selector_t);

		//creates the level buttons
		for (int i = 0; i < LEVELS; i++) {
			Levels[i].create("Level_Selector");
		}

	}

}

void GUI::transition() {

	//changes the current screen according to what is happening on screen
	if (this->Play.triggered == true) {

		Current_Screen = level_selector_s;
		current_state = level_selector;

		this->construct_screen("level_selector");

		//spawns the level buttons equality distant

		sf::Vector2f spacing = {
			(1368 / (2 * LEVELS_PER_ROW - 1 + 2)),
			(768 / (2 * LEVELS_PER_COLUMN - 1 + 2))
		};

		for (int i = 0; i < LEVELS_PER_ROW; i++) {
			for (int j = 0; j < LEVELS_PER_COLUMN; j++) {

				//translate 2d to 1d
				int index = i * LEVELS_PER_COLUMN + j;

				//sets the position of the level buttons
				Levels[index].initialize(sf::Vector2f(
					(2 * i + 1) * spacing.x + Levels[index].get_sprite()->getOrigin().x * Levels[index].get_sprite()->getScale().x,
					(2 * j + 1) * spacing.y + Levels[index].get_sprite()->getOrigin().y
				), sf::Vector2f(1.3, 1.3));
			}
		}

	}

}