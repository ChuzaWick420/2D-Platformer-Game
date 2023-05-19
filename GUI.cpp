#include "GUI.hpp"

void GUI::init() {

	//loads the main menu
	m_menu_t.loadFromFile("assets/GUI/mainmenu.jpg");

	//sets the texture to the sprite
	m_menu_s.setTexture(m_menu_t);

	//sets current displayed screen to the main menu
	Current_Screen = m_menu_s;

	for (int i = 0; i < 4; i++) {
		//loads play button
		play_t[i].loadFromFile("assets/GUI/Buttons/Play/" + std::to_string(i + 1) + ".png");
	}

	//sets the texture to the sprite
	play_s.setTexture(play_t[0]);

	//scale it up a little bit
	play_s.setScale(2.5, 2.5);

	//sets origin
	play_s.setOrigin(play_t[0].getSize().x / 2, play_t[0].getSize().y / 2);

}

void GUI::render(sf::RenderWindow& target_window) {
	//draws the current screen
	target_window.draw(Current_Screen);
	target_window.draw(play_s);
}

void GUI::resize(sf::Vector2f size) {
	//gets the size of the window and resizes the current screen to fit it
	m_menu_s.setScale(size.x / Current_Screen.getGlobalBounds().width, size.y / Current_Screen.getGlobalBounds().height);

	Current_Screen = m_menu_s;

	//sets the position of the play button in middle of screen
	play_s.setPosition(Current_Screen.getGlobalBounds().width / 2, Current_Screen.getGlobalBounds().height / 2);
}

void GUI::animate(int frame_number) {
	//sets the texture of the play button to the frame number
	play_s.setTexture(play_t[frame_number]);
}