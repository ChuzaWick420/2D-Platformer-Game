#include <iostream>

#include "Player.hpp"
#include "physics.hpp"
#include "Level.hpp"
#include "Controller.hpp"

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

	player.player_sprite.setOrigin(sf::Vector2f(player.idle_t[0].getSize().x / 2, player.idle_t[0].getSize().y / 2));

	player.create_hitbox(
		player.player_sprite.getPosition(), 
		{
			player.player_sprite.getGlobalBounds().width, 
			player.player_sprite.getGlobalBounds().height 
		}
	);

	//debug player's position
	std::cout << player.player_sprite.getPosition().x << ", " << player.player_sprite.getPosition().y << std::endl;

	//variables
	sf::Clock game_ticks, player_ticks, fps, physics_clock;

	float frames = 20;
	float game_update_timer = 50;	//milliseconds
	float physics_timer = 1;	//milliseconds
	float fps_timer = 1;

	const int animation_frames = 10;
	int current_frame = 0;

	float gravity_coefficient = 0;

	//game loop
	while (game_window.isOpen()) {

		sf::Event window_events;

		while (game_window.pollEvent(window_events)){

			if (window_events.type == sf::Event::Closed)
				game_window.close();

		}

		//handles physics timings
		if (physics_clock.getElapsedTime().asMilliseconds() >= physics_timer) {

			apply_gravity(player, level.hitboxes[0], gravity_coefficient, player.on_ground);

			control(player);

			//updates hitboxes
			player.get_hitbox().update(player.player_sprite);

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

			//reset the ticks
			game_ticks.restart();

		}

		//handles fps and drawing timings
		if (fps.getElapsedTime().asMilliseconds() >= fps_timer) {

			game_window.clear();
			level.render(game_window);
			player.render(game_window);
			player.get_hitbox().render(game_window);

			//draw the ground tile hitbox under player
			if(player.on_ground == true)
				level.hitboxes[player.player_sprite.getPosition().x / 64].render(game_window);

			game_window.display();

			fps.restart();
		}

	}

	return 0;
}