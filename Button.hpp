#pragma once

#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

#define button_frames 4

class Button{

public:

	Button() {};

	void create(std::string path);

	//sets position, scale of the button
	void initialize(sf::Vector2f position, sf::Vector2f scale);

	void animate(sf::Mouse cursor);

	void render(sf::RenderWindow& target_window);

	sf::Sprite* get_sprite() { return &this->frames_s; }

private:
	
	enum state {
		neutral,
		hover,
		up,
		down
	};

	state current_state = neutral;

	//texture for the button
	sf::Texture frames_t[button_frames];

	//currently displayed frame (as a sprite)
	sf::Sprite frames_s;

	int frame_counter = 0;

};