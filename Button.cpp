#include "Button.hpp"

void Button::create(std::string path) {
	
	//loads the frames from the path
	for (int frame = 0; frame < button_frames; frame++) {

		//loads the frames 1 by 1
		this->frames_t[frame].loadFromFile("assets/GUI/Buttons/" + path + "/" + std::to_string(frame + 1) + ".png");

	}

	//initializes the sprite
	this->frames_s.setTexture(this->frames_t[0]);

	//scale it up a little bit
	this->frames_s.setScale(2.5, 2.5);

	//sets origin
	this->frames_s.setOrigin(this->frames_t[0].getSize().x / 2, this->frames_t[0].getSize().y / 2);

}

void Button::initialize(sf::Vector2f position, sf::Vector2f scale) {
	//sets position and scale
	this->frames_s.setPosition(position);
	this->frames_s.setScale(scale);
}

void Button::render(sf::RenderWindow& target_window) {
	//renders the button
	target_window.draw(this->frames_s);
}

void Button::animate(sf::Mouse cursor) {

	//sets the states of the button according to cursor's state and position
	//if the cursor is hovering over the button
	if (this->frames_s.getGlobalBounds().contains(sf::Vector2f(cursor.getPosition()))) {

		//if player is clicking the button
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			this->current_state = down;

		//if player is not clicking the button
		//check if his previous state was down
		else if (this->current_state == down || (this->frame_counter != 0))
			//if it was, set the state to up because we are lifting the button after is was pressed
			this->current_state = up;
		
		//if the player is not clicking the button and his previous state was not down
		else
			//set the state to hover because the cursor is hovering over the button
			this->current_state = hover;
	}

	else
		this->current_state = neutral;

	//animates the button
	switch (this->current_state) {

	case up:
		//set the texture to the time where button is fully down
		this->frames_s.setTexture(this->frames_t[this->frame_counter - 1]);
		//decrements the frame counter
		this->frame_counter--;
		//if the counter goes out of range (below 1)
		if (this->frame_counter < 0)
			this->frame_counter = 0;

		break;

	case down:
		//set the texture to the time where button is fully up
		this->frames_s.setTexture(this->frames_t[frame_counter]);
		//increment the frame counter
		this->frame_counter++;
		//if the button is held, keep it at the last frame
		if (this->frame_counter > button_frames - 1)
			this->frame_counter = button_frames - 1;

		break;

	default:
		break;

	}

}