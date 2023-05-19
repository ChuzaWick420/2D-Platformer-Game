#pragma once

#include <SFML/Graphics.hpp>

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

private:

	//textures of the GUI componenets
	sf::Texture 
		m_menu_t, play_t[4]
	;
	
	//sprites of the GUI components
	sf::Sprite 
		m_menu_s, play_s
	;
};