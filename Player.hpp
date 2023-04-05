#pragma once
#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>

class Player{

public:
	sf::Texture walk_t[10], idle_t[10], jump_t[10], dead_t[10];

	Player();

	enum direction {
		R, L
	};

	enum state {
		Dead, Idle, Walk, Jump
	};

	state current_state = Idle;
	direction current_direction = R;

	bool on_ground = true;

	sf::Sprite player_current;

	float scale = 0.3;
	float speed = 10;

	void render(sf::RenderWindow& target_window);

	void animate(state is_doing, int frame_number);

	void jump();

};