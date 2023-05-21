#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Game.h"

#define MAX_NUMBER_OF_ITEMS 3
class MainMenu
{
public:
	MainMenu(float width, float height);
	void draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	void ready_game();
	void draw_tlo(sf::RenderWindow& window);
	void Odpalaj();
	int GetPressedItem() { return selectedItemIndex; }
	~MainMenu();
private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text _mainmenu[MAX_NUMBER_OF_ITEMS];
	sf::Text title;
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
	sf::RectangleShape button[MAX_NUMBER_OF_ITEMS];
	
};

