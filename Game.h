#pragma once
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "player.h"
#include "platform.h"
#include "moving_platform.h"
#include "MainMenu.h"
class Game
{ public:
	Game();
	void play();
private:
	void generate_platform(); 
	void move_all(sf::Vector2f ruch); 
	void add_score(player& play);
	void next_screen(player &play, const sf::Time& elapsed);
	void ready_game(); 
	void set_viev(player& play); 
	void draw_tlo(sf::RenderWindow &window); 
	float generate_rand_dist(); 
private:
	std::vector<platform*> platformy;
	sf::Texture tlo1; 
	sf::Texture tlo2;
	sf::Texture tlo3;
	sf::Texture tlo4;
	sf::Texture tlo5;
	sf::Event event;
	sf::Sprite tlo_s;
	sf::Sprite tlo_s2;
	sf::Sprite tlo_s3;
	sf::Sprite tlo_s4;
	sf::Sprite tlo_s5;

	sf::Vector2f move_cos;
	sf::RenderWindow window; // (sf::VideoMode(800, 1000), "Cloud tower");

	float max_y; 
	int score = 0; 
};

