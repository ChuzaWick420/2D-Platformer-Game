#include <iostream>

#include "Player.hpp"
#include "physics.hpp"
#include "Level.hpp"
#include "Controller.hpp"
#include "GUI.hpp"

#define WINDOW_WIDTH 1368
#define WINDOW_HEIGHT 768

int main() {

	//temporary
	sf::Texture loading_screen_t;
	loading_screen_t.loadFromFile("assets/GUI/loading_screen.jpg");

	sf::Sprite loading_screen_s;
	loading_screen_s.setTexture(loading_screen_t);

	//window
	sf::RenderWindow game_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Plateformer", sf::Style::Default);

	//window icon
	sf::Image w_icon;
	w_icon.loadFromFile("assets/bullet.png");

	game_window.setIcon(w_icon.getSize().x, w_icon.getSize().y, w_icon.getPixelsPtr());

	//GUI manager
	GUI game;

	//resizes the GUI to fit the window
	game.resize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));

	//pointers pointing to objects of the game
	Level* level_ptr = nullptr;
	Player* player_ptr = nullptr;

	sf::Vector2f hitbox_offset = { 0 , 30 };		//10 pixels for feet and head

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

	float gravity_coefficient = 0;

	int active_level = -1;

	//game loop
	while (game_window.isOpen()) {

		sf::Event window_events;

		while (game_window.pollEvent(window_events)){

			if (window_events.type == sf::Event::Closed) {

				//delete the objects
				if (level_ptr != nullptr && player_ptr != nullptr) {
					delete level_ptr;
					delete player_ptr;
				}

				game_window.close();

				return 0;
			}

		}

		//handles game timings
		if (game_ticks.getElapsedTime().asMilliseconds() >= game_update_timer) {

			//sets the pointers according to the current state
			switch (game.current_state) {
			
				case game.main_menu:
					game.Play.animate(game_mouse);
					break;

				case game.level_selector:
					for (int i = 0; i < LEVELS_PER_ROW; i++) {
						for (int j = 0; j < LEVELS_PER_COLUMN; j++) {
							int index = j * LEVELS_PER_ROW + i;
							game.levels[index].Level.animate(game_mouse);

							//store the index of button that was clicked
							if (game.levels[index].Level.triggered == true)
								active_level = index;
						}
					}
					break;

				case game.level_screen:

					//make the level if pointer was empty, otherwise skip the creation process
					if (level_ptr == nullptr) {

						level_ptr = new Level;

						(*level_ptr).create(std::to_string(active_level + 1) + ".png", "map.png", sf::Vector2u(64, 64), sf::Vector2u(16, 16));
						(*level_ptr).create_hitboxes(sf::Vector2u(64, 64));
	
						game_window.setView((*level_ptr).camera);

					}

					if (player_ptr == nullptr) {

						player_ptr = new Player;

						(*player_ptr).player_sprite.setOrigin(sf::Vector2f((*player_ptr).idle_t[0].getSize().x / 2, (*player_ptr).idle_t[0].getSize().y / 2));
						(*player_ptr).player_sprite.setPosition(64 * 6, 64 * 6);

						(*player_ptr).create_hitbox(
							{

								(*player_ptr).player_sprite.getPosition().x - (*player_ptr).player_sprite.getGlobalBounds().width / 2,
								(*player_ptr).player_sprite.getPosition().y - (*player_ptr).player_sprite.getGlobalBounds().height / 2 + hitbox_offset.y		//10 for head

							},
							{
								(*player_ptr).player_sprite.getGlobalBounds().width,
								(*player_ptr).player_sprite.getGlobalBounds().height - 10 - hitbox_offset.y		//10 for feet, 10 for head
							}
						);

					}

					//animation

					//player
					if (current_frame_player < animation_frames_player) {
						(*player_ptr).animate((*player_ptr).current_state, current_frame_player);
						current_frame_player++;
					}

					else
						current_frame_player = 0;	//reset

			default:
				break;
			}

			//moves between different GUI screens
			game.transition();

			//reset the ticks
			game_ticks.restart();

		}

		//handles physics timings
		if (physics_clock.getElapsedTime().asMilliseconds() >= physics_timer && game.current_state == game.level_screen) {
			
			if (player_ptr != nullptr && level_ptr != nullptr) {
				
				control(*player_ptr);
				
				//updates hitboxes
				(*player_ptr).get_hitbox()->update((*player_ptr).player_sprite, hitbox_offset);
	
				//applies gravity to objects
				apply_gravity(*player_ptr, *level_ptr, gravity_coefficient);
	
				(*level_ptr).update(*player_ptr, game_window);
			
			}

			physics_clock.restart();

		}

		//handles fps and drawing timings
		if (fps.getElapsedTime().asMilliseconds() >= fps_timer) {

			game_window.clear();

			game_window.draw(loading_screen_s);

			if (level_ptr != nullptr)
				(*level_ptr).render(game_window);

			if (player_ptr != nullptr) {
				(*player_ptr).render(game_window);
				(*player_ptr).get_hitbox()->render(game_window);
			}

			game.render(game_window);

			game_window.display();

			fps.restart();
		}

	}

	return 0;
}