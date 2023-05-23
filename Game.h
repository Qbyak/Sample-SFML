#pragma once
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "player.h"
#include "platform.h"
#include "moving_platform.h"
#include "MainMenu.h"
#include "Background.h"
class Game:public Background
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
	

	sf::Vector2f move_cos;
	sf::RenderWindow window; // (sf::VideoMode(800, 1000), "Cloud tower");

	float max_y; 
	int score = 0; 
};

