#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Background.h"
#include <vector>
#define MAX_NUMBER_OF_BUTTONS 3

class MainMenu
{
public:
	void PlayMainMenu(sf::RenderWindow* window);//pêtla menu g³ównego

	void PlayPauseMenu(sf::RenderWindow* window,player &play);
	MainMenu();//konstruktor menu, tworzenie przycisków
	~MainMenu();
private:
	void draw(sf::RenderWindow *window);//rysowanie przycisków i tytu³u
	void MoveUp();//przesuwanie w górê
	void MoveDown();//przesuwanie w dó³
	int GetPressedItem();//getter selectedItemIndex
	//void draw_tlo(sf::RenderWindow*window);
	void MenuButtons(float width, float height);
	void PauseButtons(sf::RenderWindow* window);
	void OptionButtons(float width, float height);
	void PlayOptions();
	void odczyt();//odczyt do taveli wyników
	void autorzy();//okno wyœwietlaj¹ce autorów
	//deklaracje elementów sk³adaj¹cych siê na przycisk
	enum buttons;
	int selectedItemIndex;
	std::vector<sf::Text> buttontext;
	sf::Text title;
	sf::Font font;
	std::vector<sf::FloatRect> textbounds;
	std::vector<sf::FloatRect> buttonbounds;
	std::vector<sf::RectangleShape> button;
	sf::RectangleShape pauseBackground;
	Background background;
	sf::View view_pause;
	// do odczytu
	sf::Text y;
	std::vector<sf::Text> tab;
	struct do_zapisu
	{
		int score;
		std::string name;
	};
	std::vector<do_zapisu> posortowany;
	friend std::ostream& operator <<(std::ostream& s, const do_zapisu& v)
	{
		return s << "nick: " << v.name << ", wynik: " << v.score << std::endl;
	}
	//pomocnicze
	sf::Vector2f ruch;
	
};
