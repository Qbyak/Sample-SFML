#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Game.h"

#include <vector>
#define MAX_NUMBER_OF_BUTTONS 3

class MainMenu
{
public:
	void Play(sf::RenderWindow& window);
	MainMenu(float width, float height);
	~MainMenu();
private:
	void draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItemIndex; }
	enum buttons;
	int selectedItemIndex;
	sf::Text buttontext[MAX_NUMBER_OF_BUTTONS];
	sf::Text title;
	sf::Font font;
	sf::RectangleShape button[MAX_NUMBER_OF_BUTTONS];
	
};
