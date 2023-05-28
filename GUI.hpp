#pragma once

#include <SFML/Graphics.hpp>

#include "Button.hpp"

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

	Button Play;

private:

	//textures of the GUI componenets
	sf::Texture 
		m_menu_t, level_selector_t
	;
	
	//sprites of the GUI components
	sf::Sprite 
		m_menu_s, level_selector_s
	;
};