#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "player.h"
#include "platform.h"
#include "moving_platform.h"
#include "Background.h"
#include "disappearing_platform.h"
#include "coin.h"
#include "coin_counter.h"
#include "MainMenu.h"
#include "heart.h"
class Game
{ public:
	Game();
	void play();
	//void draw_tlo(sf::RenderWindow* window);
private:
	// funkcje generujace 
	void generate_platform(player play); // generuje platformy z szansa na wygenerowanie monety na jednej z nich
	void generate_bombs(player play);

	// funkcje przygotowywujace
	void ready_game();
	void ready_background_texture(); 

	// funkcje updatujace
	void update_all(sf::RenderWindow* window, player& player); // updatuje kazda platforme 
    void death(player& player ,  sf::RenderWindow* window); // ekran smierci 
    void move_all(sf::Vector2f ruch); // rusza wszystkie platformy 
	void next_screen(player &player); // przygotowanie nastepnej klatki 
	void pauza(sf::RenderWindow *window,player& gracz); // ekran pauzy 
	void GameOver(player& play);// ekran game over
	void close_window(sf::RenderWindow *window); 
	void update_view(sf::RenderWindow *window , player player); 
	//
	void move_bombs(); // rusza bomby 

	void draw_all(sf::RenderWindow* window , player &player , bool if_coin_count , bool if_player);	
	// funkcja obslugujaca minimape
	void update_minimap(player player);
	//funkcje zapis
	void zapis(player& play,std::string nick);

private:
	sf::RenderWindow *window;
	sf::RenderWindow* minimap; 
	// vectory obiektow na planszy 
	std::vector<platform*> *platformy;
	std::vector<bomb*> *bomby; 
	std::vector<coin*> *monety; 
	std::vector<heart*> *serca;

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
	float game_speed; 
	// 'widoki' gry , minimapa oraz glowne okno 
	sf::View view_game;
	sf::View viev_minimap;
	// 
	int map_number; // numer mapy
	// obiekty potrzebne do gry 
	Background background; // tlo
	coin_counter  licznik_gracza; // licznik gracza
	player gracz;  // gracz
	MainMenu menu; // obiekt menu odpowiezialny za pauzy itp 
};

