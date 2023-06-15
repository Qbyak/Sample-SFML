#pragma once
#include "coin.h"
#include "player.h"
class coin_counter : public coin
{public:
	coin_counter(sf::Vector2f pozycja);
	coin_counter(); 
	void aktualizuj_wynik(player gracz , sf::View widok , sf::RenderWindow *window); 
    void draw(sf::RenderWindow* window); 
private:
	void update_hearts(player gracz);
private:
	sf::Font font1;
	sf::Text *tekst;
	std::vector<heart*> *serca_zycia; // wektor obiektow odpowiadajacych zycia gracza
	sf::Vector2f pozycja;
	int number;
};


