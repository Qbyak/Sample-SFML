#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Game.h"
#include "Background.h"
#define MAX_NUMBER_OF_ITEMS 3
class MainMenu:public Background
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
	enum buttons;
	~MainMenu();
private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text _mainmenu[MAX_NUMBER_OF_ITEMS];
	sf::Text title;
	sf::RectangleShape button[MAX_NUMBER_OF_ITEMS];
	
};
