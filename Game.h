#pragma once
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "player.h"
#include "platform.h"
#include "moving_platform.h"
#include "disappearing_platform.h"

#include "MainMenu.h"
#include "PauseMenu.h"
class Game
{ public:
	Game();
	void play();
		
private:
	// funkcje generujace 
	void generate_platform(); 
	void generate_bombs();
	float generate_rand_dist(); // generuje dystans w okreslonym przedziale , aby gracz doskoczyl do kazdej platformy 

	// funkcje przygotowywujace
	void ready_game();
	void ready_background_texture();

	// funkcje updatujace
	void update_all(player& gracz, const sf::Time& elapsed); // updatuje kazda platforme 
    void death(player& gracz ,  sf::RenderWindow& window); // ekran smierci 
    void move_all(sf::Vector2f ruch); // rusza wszystkie platformy 
	void next_screen(player &gracz, const sf::Time& elapsed); // przygotowanie nastepnej klatki 
	void pauza(sf::RenderWindow &window, player& gracz); // ekran pauzy 
	void main_menu(sf::RenderWindow& window);

	// funkcje rysujace	
	void draw_all(sf::RenderWindow& window);
	void draw_tlo(sf::RenderWindow &window); 

private:
	// vectory obiektow na planszy 
	std::vector<platform*> platformy;
	std::vector<bomb*> bomby; 

	// zmienne czasowe do animacji bomby
	sf::Clock bomb_clock; 
	sf::Time bomb_time; 

	// tekstury oraz sprite'y dla tla
	sf::Texture tlo1; 
	sf::Texture tlo2;
	sf::Texture tlo3;
	sf::Texture tlo4;
	sf::Texture tlo5;
	sf::Sprite tlo_s;
	sf::Sprite tlo_s2;
	sf::Sprite tlo_s3;
	sf::Sprite tlo_s4;
	sf::Sprite tlo_s5;

	// glowna zmienna event
	sf::Event event;

	// zmienne dodatkowe
	sf::Clock clock;
	bool pauza_bool;
	bool menu_loop;
	float game_speed;
	float player_score; 
};
