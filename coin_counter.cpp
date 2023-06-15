#include "coin_counter.h"

coin_counter::coin_counter(sf::Vector2f pozycja) : coin(pozycja) // inicjalizacja zmiennych 
{
	font1.loadFromFile("./assets/FronzyFreeTrial-mLVlP.otf");
	tekst = new sf::Text("0", font1);
	tekst->setScale(2, 2);
	setScale(3, 3); 
	tekst->setFillColor(sf::Color::Yellow);
	serca_zycia = new std::vector<heart*>; 
	number = 0;
}
coin_counter::coin_counter() : coin(sf::Vector2f(0,0)) // inicjalizacja zmiennych
{
	font1.loadFromFile("./assets/FronzyFreeTrial-mLVlP.otf");
	tekst = new sf::Text("0", font1);
	tekst->setFillColor(sf::Color::Yellow);
	tekst->setScale(2, 2);
	setScale(3, 3);
	serca_zycia = new std::vector<heart*>;  	
	number = 0;
}


void coin_counter::aktualizuj_wynik(player gracz , sf::View widok , sf::RenderWindow *window) // aktualizacja parametow jak i polozenia
{
	setPosition(widok.getCenter().x + 300, widok.getCenter().y - 500); // ustawianie pozycji w rogu
	update(); 
	update_hearts(gracz); 
	tekst->setPosition(getPosition().x + 30,getPosition().y + 50); // ustawianie pozycji w rogu
	tekst->setString(std::to_string(gracz.return_score()));
	number = 0; // na podstawie ilosci zyc w klasie gracza 
	if (serca_zycia->size() > 0)
	{
		for (auto& x : *serca_zycia)
		{
			x->setPosition(getPosition().x - 30 + 40 * number, getPosition().y + 150); // ustawianie pozycji w rogu 
				number++; 
		}
	}
}

void coin_counter::draw(sf::RenderWindow* window) // rysowanie
{
	window->draw(*this);
	window->draw(*tekst); 
	for (auto s : *serca_zycia)
	{
		window->draw(*s); 
	}
}

void coin_counter::update_hearts(player gracz) // aktualizacja ilosci serc 
{
	if (gracz.return_lives() > serca_zycia->size())
	{
		serca_zycia->emplace_back(new heart(sf::Vector2f(0, 0), sf::Vector2f(0.8, 0.8))); 
	}
	if (gracz.return_lives() < serca_zycia->size() && serca_zycia->size() > 0)
	{
		auto x = std::find(serca_zycia->begin(), serca_zycia->end(), serca_zycia->back());
		serca_zycia->erase(x); 
	}
}
