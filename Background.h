#pragma once
#include <iostream>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "player.h"
class Background
{
public:
	void ready_background_texture();//Przygotowanie t³a
	void draw_tlo(sf::RenderWindow *window);//rysowanie t³a w grze	
	void draw_menu_background(sf::RenderWindow* window);//rysowanie t³a w menu, opcjach,autorach,tabeli wyników
	void draw_pause_background(sf::RenderWindow* window, player& play);//rysowanie t³a w pauzie
private:

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
};