#pragma once

#include <SFML/Graphics.hpp>

#include "Button.hpp"

#define LEVELS_PER_ROW 4
#define LEVELS_PER_COLUMN 3

#define LEVELS LEVELS_PER_ROW * LEVELS_PER_COLUMN

class GUI {

public:

	//empty constructor
	GUI() { init(); };

	//holds what is currently being displayed
	sf::Sprite Current_Screen;

	void init();

	void render(sf::RenderWindow& target_window);

	void resize(sf::Vector2f size);

	void animate(int frame_number);

	void transition();

	Button Play;

	struct Level_Button {
		Button Level;
		bool unlocked = false;
	};

	Level_Button levels[LEVELS];

	void construct_screen(std::string type);

	enum state {
		main_menu,
		level_selector,
		level_screen
	};

	state current_state = main_menu;

private:

	//textures of the GUI componenets
	sf::Texture 
		m_menu_t, level_selector_t, level_screen_t
	;
	
	//sprites of the GUI components
	sf::Sprite 
		m_menu_s, level_selector_s, level_screen_s
	;
};