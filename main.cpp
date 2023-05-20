#include <iostream>

#include "Player.hpp"
#include "physics.hpp"
#include "Level.hpp"
#include "Controller.hpp"
#include "GUI.hpp"

#define window_width 1368
#define window_height 768

int main() {

	//window
	sf::RenderWindow game_window(sf::VideoMode(window_width, window_height), "Plateformer", sf::Style::Default);

	//GUI
	GUI game;

	//resizes the GUI to fit the window
	game.resize(sf::Vector2f(window_width, window_height));

	Level level;
	level.create("1.png", "map.png", sf::Vector2u(64, 64), sf::Vector2u(16, 16));
	level.create_hitboxes(sf::Vector2u(64, 64));

	//window icon
	sf::Image w_icon;
	w_icon.loadFromFile("assets/bullet.png");

	game_window.setIcon(w_icon.getSize().x, w_icon.getSize().y, w_icon.getPixelsPtr());

	Player player;

	player.player_sprite.setOrigin(sf::Vector2f(player.idle_t[0].getSize().x / 2, player.idle_t[0].getSize().y / 2));

	player.player_sprite.setPosition(64 * 6, 64 * 6);

	sf::Vector2f hitbox_offset = {0 , 30};		//10 pixels for feet and head

	player.create_hitbox(
		{

			player.player_sprite.getPosition().x - player.player_sprite.getGlobalBounds().width / 2,
			player.player_sprite.getPosition().y - player.player_sprite.getGlobalBounds().height / 2 + hitbox_offset.y		//10 for head

		},
		{
			player.player_sprite.getGlobalBounds().width,
			player.player_sprite.getGlobalBounds().height - 10 - hitbox_offset.y		//10 for feet, 10 for head
		}
	);

	//variables
	sf::Clock game_ticks, player_ticks, fps, physics_clock;

	sf::Mouse game_mouse;

	float frames = 20;
	float game_update_timer = 50;	//milliseconds
	float physics_timer = 1;	//milliseconds
	float fps_timer = 1;

	const int animation_frames_player = 10;
	const int animation_frames_button = 4;
	int current_frame_player = 0;
	int current_frame_button = 0;

	float gravity_coefficient = 0;

	game_window.setView(level.camera);

	//game loop
	while (game_window.isOpen()) {

		sf::Event window_events;

		while (game_window.pollEvent(window_events)){

			if (window_events.type == sf::Event::Closed)
				game_window.close();

		}

		//handles physics timings
		if (physics_clock.getElapsedTime().asMilliseconds() >= physics_timer) {

			control(player);

			//updates hitboxes
			player.get_hitbox()->update(player.player_sprite, hitbox_offset);

			//applies gravity to objects
			apply_gravity(player, level, gravity_coefficient);

			level.update(player, game_window);

			physics_clock.restart();

		}

		//handles game timings
		if (game_ticks.getElapsedTime().asMilliseconds() >= game_update_timer) {

			//animation
			
			//player
			if (current_frame_player < animation_frames_player) {
				player.animate(player.current_state, current_frame_player);
				current_frame_player++;
			}

			else
				current_frame_player = 0;	//reset

			game.Play.animate(game_mouse);

			//reset the ticks
			game_ticks.restart();

		}

		//handles fps and drawing timings
		if (fps.getElapsedTime().asMilliseconds() >= fps_timer) {

			game_window.clear();

			level.render(game_window);
			player.render(game_window);
			player.get_hitbox()->render(game_window);

			game.render(game_window);

			game_window.display();

			fps.restart();
		}

	}

	return 0;
}