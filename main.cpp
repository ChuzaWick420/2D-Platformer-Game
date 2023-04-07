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
	
	sf::Clock game_ticks, player_ticks, fps;

	float frames = 20;
	float game_update_timer = 50;	//milliseconds

	const int animation_frames = 10;
	int current_frame = 0;

	while (game_window.isOpen()) {

		sf::Event window_events;

		while (game_window.pollEvent(window_events)){

			if (window_events.type == sf::Event::Closed)
				game_window.close();

		}

		if (game_ticks.getElapsedTime().asMilliseconds() >= game_update_timer) {
			
			game_window.clear();
			level.render(game_window);
			player.render(game_window);
			game_window.display();

			bool change_dir = control(player);

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
					player.player_current.move(-player.scale * player.idle_t[0].getSize().x, 0);

				if (player.current_direction == Player::L)
					player.player_current.move(player.scale * player.idle_t[0].getSize().x, 0);

			}

			//reset the ticks
			game_ticks.restart();

		}

	}

	return 0;
}