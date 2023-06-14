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
	void PlayMainMenu(sf::RenderWindow* window, sf::RenderWindow* minimap);//pêtla menu g³ównego
	void GameOver(player& gracz, sf::RenderWindow* window, std::vector<platform*>* platformy, std::vector<bomb*>* bomby, std::vector<coin*>* monety,
		sf::RenderWindow* minimap); //tworzenie okna game over
	void PlayPauseMenu(sf::RenderWindow* window, sf::RenderWindow* minimap, player& play);//pêtla menu pauzy
	MainMenu();//konstruktor menu, wczytywanie tekstur t³a
	~MainMenu();
private:
	void draw(sf::RenderWindow *window);//rysowanie przycisków i tytu³u
	void MoveUp();//przesuwanie w górê
	void MoveDown();//przesuwanie w dó³
	int GetPressedItem();//getter selectedItemIndex
	void MenuButtons(float width, float height);//przyciski menu g³ównego
	void PauseButtons(sf::RenderWindow* window);//przyciski menu pauzy
	void OptionButtons(float width, float height);//przyciski menu opcji
	void PlayOptions();//pêtla menu opcji
	void odczyt();//odczyt do tabeli wyników
	void autorzy();//okno wyœwietlaj¹ce autorów
	void zapis(player& play, std::string nick);//zapis wyniku oraz nicku do pliku csv
	void LoadFonts();//wczytywanie czcionek
private:
	//deklaracje elementów sk³adaj¹cych siê na przycisk
	enum buttons;
	int selectedButtonIndex;//indeks przycisku
	std::vector<sf::Text> buttontext;//wektor tekstu znajdujacego sie na przycisku
	sf::Text title;//tytul danego menu
	sf::Font font, text_font;//poszczegolne czcionki
	std::vector<sf::FloatRect> textbounds;//wektor granic tekstu na przyciskach, sluzy do ustalenia rozmiarow przyciskow
	std::vector<sf::FloatRect> buttonbounds;//wektor granic przyciskow, sluzy do ustalenia srodka 
	std::vector<sf::RectangleShape> button;//przycisk
	Background background;//obiekt tla
	sf::View view_pause;//widok pauzy, ustawianie pod aktualna pozycje gracza
	// do odczytu

	std::vector<sf::Text> tab;//wektor tekstow na tablicy wynikow
	struct do_zapisu//struktura sluzaca do zapisywania wynikow
	{
		int score=0;
		std::string name;
	};
	std::vector<do_zapisu> posortowany;//wektor trzymajacy posortowane wyniki
	friend std::ostream& operator <<(std::ostream& s, const do_zapisu& v)//przeciazanie odczytu tablicy wynikow w konsoli
	{
		return s << "nick: " << v.name << ", wynik: " << v.score << std::endl;
	}
};
