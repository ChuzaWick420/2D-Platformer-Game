#include "src/GUI.hpp"

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

void GUI::fit(sf::RenderWindow& t_window) {

	//scale the menu according to the window size
	this->m_menu_s.setScale(
		t_window.getSize().x / this->m_menu_s.getGlobalBounds().width,
		t_window.getSize().y / this->m_menu_s.getGlobalBounds().height
	);

	Current_Screen = m_menu_s;

	//initialize the play button once the screen is resized
	this->Play.initialize(sf::Vector2f(t_window.getSize().x / 2, t_window.getSize().y / 2), sf::Vector2f(3, 3));

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

	//vertical
	float view_height = t_window.getSize().x / 16.0f * 9.0f;			//view's height as a function of window's width
	float vertical_offset = (t_window.getSize().y - view_height) / 2;

	//horizontal
	float view_width = t_window.getSize().y / 9.0f * 16.0f;				//view's width as a function of window's height
	float horizontal_offset = (t_window.getSize().x - view_width) / 2;

	sf::FloatRect visible_region(
		sf::Vector2f(0, 0),			//position, which defines where the rendering of texture starts
		sf::Vector2f(this->m_menu_s.getGlobalBounds().width, this->m_menu_s.getGlobalBounds().height)	//size, which defines the size of the texture to render
	);

	//sets the rectangle as view
	sf::View visible_view(visible_region);

	//checks the extreme direction
	if (t_window.getSize().x / t_window.getSize().y <= 16.0f / 9.0f) {

		visible_view.setViewport(sf::FloatRect(
			0.0f,										//Left offset scale 
			vertical_offset / t_window.getSize().y,		//Top offset scale
			1.0f,										//Width scale
			view_height / t_window.getSize().y			//Height scale
		));

	}

	else {

		visible_view.setViewport(sf::FloatRect(
			horizontal_offset / t_window.getSize().x,	//Left offset scale 
			0.0f,										//Top offset scale
			view_width / t_window.getSize().x,			//Width scale
			1.0f										//Height scale
		));
	}

	//finally, resets the window view
	t_window.setView(sf::View(visible_view));

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