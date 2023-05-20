#include "GUI.hpp"

void GUI::init() {

	//loads the main menu
	m_menu_t.loadFromFile("assets/GUI/mainmenu.jpg");

	//sets the texture to the sprite
	m_menu_s.setTexture(m_menu_t);

	//sets current displayed screen to the main menu
	Current_Screen = m_menu_s;

	//loads the play button
	Play.create("Play");

}

void GUI::render(sf::RenderWindow& target_window) {
	//draws the current screen
	target_window.draw(Current_Screen);
	target_window.draw(*Play.get_sprite());
}

void GUI::resize(sf::Vector2f size) {
	//gets the size of the window and resizes the current screen to fit it
	m_menu_s.setScale(size.x / Current_Screen.getGlobalBounds().width, size.y / Current_Screen.getGlobalBounds().height);

	Current_Screen = m_menu_s;

	//initialize the play button once the screen is resized
	Play.initialize(sf::Vector2f(size.x / 2, size.y / 2), sf::Vector2f(2.5, 2.5));

}

void GUI::animate(int frame_number) {

}