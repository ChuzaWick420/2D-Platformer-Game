#pragma once
#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>

#include "Hitbox.hpp"

class Player{

public:

	bool is_jumping = false;

	sf::Texture walk_t[10], idle_t[10], jump_t[10], dead_t[10];

	Player();

	enum direction {
		R, L
	};

	enum state {
		Dead, Idle, Walk, Jump, Fall
	};

	state current_state = Idle;
	direction current_direction = R;

	bool on_ground = false;

	sf::Sprite player_sprite;

	float scale = 0.3;
	float speed = 1;

	void render(sf::RenderWindow& target_window);

	void animate(state is_doing, int frame_number);

	void jump(float force);

	void create_hitbox(sf::Vector2f t_position, sf::Vector2f t_size);

	sf::Vector2f get_position();

	void set_position(sf::Vector2f t_position);

	Hitbox get_hitbox();

	float get_jump_force();

	void set_jump_force(float value);

private:

	float jump_force = 3;

	Hitbox hitbox;

	sf::Vector2f position;

};