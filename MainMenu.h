#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Game.h"
#include "Background.h"
#include <vector>
#define MAX_NUMBER_OF_BUTTONS 3

class MainMenu
{
public:
	void PlayMainMenu(sf::RenderWindow* window);//p�tla menu g��wnego
	void MenuButtons(float width, float height);
	void PauseButtons(float width, float height);
	MainMenu(float width, float height);//konstruktor menu, tworzenie przycisk�w
	~MainMenu();
private:
	void draw(sf::RenderWindow *window);//rysowanie przycisk�w i tytu�u
	void MoveUp();//przesuwanie w g�r�
	void MoveDown();//przesuwanie w d�
	int GetPressedItem();//getter selectedItemIndex
	//void draw_tlo(sf::RenderWindow*window);
	

	//deklaracje element�w sk�adaj�cych si� na przycisk
	enum buttons;
	int selectedItemIndex;
	sf::Text buttontext[MAX_NUMBER_OF_BUTTONS];
	sf::Text title;
	sf::Font font;
	sf::RectangleShape button[MAX_NUMBER_OF_BUTTONS], pauseBackground;
	Background background;
	
};
