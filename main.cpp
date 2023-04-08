#include <iostream>

#include "Player.hpp"
#include "physics.hpp"
#include "Level.hpp"

#define window_width 1368
#define window_height 768

int main() {

	//window
	sf::RenderWindow game_window(sf::VideoMode(window_width, window_height), "Plateformer", sf::Style::Default);

	Level level;
	level.create("1.png", sf::Vector2u(64, 64));
	level.create_hitboxes(sf::Vector2u(64, 64));

	//window icon
	sf::Image w_icon;
	w_icon.loadFromFile("assets/bullet.png");

	game_window.setIcon(w_icon.getSize().x, w_icon.getSize().y, w_icon.getPixelsPtr());

	Player player;

	player.create_hitbox(
		player.player_sprite.getPosition(), 
		{
			player.player_sprite.getGlobalBounds().width, 
			player.player_sprite.getGlobalBounds().height 
		}
	);

	//debug player's sprite size
	std::cout << player.player_sprite.getGlobalBounds().width << ", " << player.player_sprite.getGlobalBounds().height << std::endl;

	//variables
	sf::Clock game_ticks, player_ticks, fps, physics_clock;

	float frames = 20;
	float game_update_timer = 50;	//milliseconds
	float physics_timer = 1;	//milliseconds
	float fps_timer = 1;

	const int animation_frames = 10;
	int current_frame = 0;

	float gravity_coefficient = 0;

	bool change_dir;

	//game loop
	while (game_window.isOpen()) {

		sf::Event window_events;

		while (game_window.pollEvent(window_events)){

			if (window_events.type == sf::Event::Closed)
				game_window.close();

		}

		//handles physics timings
		if (physics_clock.getElapsedTime().asMilliseconds() >= physics_timer) {

			apply_gravity(player.player_sprite, level.hitboxes[0], gravity_coefficient, player.on_ground);

			change_dir = control(player);

			//updates hitboxes
			player.get_hitbox().update(player.player_sprite);

			//debug player's hitbox position
			std::cout << "Player's hitbox: " << "(" << player.get_hitbox().get_position().x << ", " << player.get_hitbox().get_position().y << ")" << std::endl;

			physics_clock.restart();

		}

		//handles game timings
		if (game_ticks.getElapsedTime().asMilliseconds() >= game_update_timer) {

			//animation
			if (current_frame < animation_frames) {
				player.animate(player.current_state, current_frame);
				current_frame++;
			}

			else
				current_frame = 0;	//reset

			//switches player's movements smoothly
			if (change_dir == true) {

				if(player.current_direction == Player::R)
					player.player_sprite.move(-player.player_sprite.getGlobalBounds().width, 0);

				if (player.current_direction == Player::L)
					player.player_sprite.move(player.player_sprite.getGlobalBounds().width, 0);

			}

			//reset the ticks
			game_ticks.restart();

		}

		//handles fps and drawing timings
		if (fps.getElapsedTime().asMilliseconds() >= fps_timer) {

			game_window.clear();
			level.render(game_window);
			player.render(game_window);
			player.get_hitbox().render(game_window);
			game_window.display();

			fps.restart();
		}

	}

	return 0;
}