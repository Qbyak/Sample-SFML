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
	void PlayMainMenu(sf::RenderWindow* window, sf::RenderWindow* minimap);//p�tla menu g��wnego
	void GameOver(player& gracz, sf::RenderWindow* window, std::vector<platform*>* platformy, std::vector<bomb*>* bomby, std::vector<coin*>* monety,
		sf::RenderWindow* minimap);
	void PlayPauseMenu(sf::RenderWindow* window, sf::RenderWindow* minimap, player& play);
	MainMenu();//konstruktor menu, tworzenie przycisk�w
	~MainMenu();
private:
	void draw(sf::RenderWindow *window);//rysowanie przycisk�w i tytu�u
	void MoveUp();//przesuwanie w g�r�
	void MoveDown();//przesuwanie w d�
	int GetPressedItem();//getter selectedItemIndex
	void MenuButtons(float width, float height);
	void PauseButtons(sf::RenderWindow* window);
	void OptionButtons(float width, float height);
	void PlayOptions();
	void odczyt();//odczyt do taveli wynik�w
	void autorzy();//okno wy�wietlaj�ce autor�w
	void zapis(player& play, std::string nick);
	void LoadFonts();
	//deklaracje element�w sk�adaj�cych si� na przycisk
	enum buttons;
	int selectedItemIndex;
	std::vector<sf::Text> buttontext;
	sf::Text title;
	sf::Font font, text_font;
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
		int score=0;
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
