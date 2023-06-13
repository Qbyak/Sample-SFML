#include "coin_counter.h"

coin_counter::coin_counter(sf::Vector2f pozycja) : coin(pozycja)
{
	font1.loadFromFile("./assets/BigSmoke.ttf");
	tekst = new sf::Text("0", font1);
	tekst->setScale(2, 2);
	setScale(3, 3); 
}
coin_counter::coin_counter() : coin(sf::Vector2f(0,0))
{
	font1.loadFromFile("./assets/BigSmoke.ttf");
	tekst = new sf::Text("0", font1);
	tekst->setScale(2, 2);
	setScale(3, 3);
}


void coin_counter::aktualizuj_wynik(player player , sf::View widok , sf::RenderWindow *window)
{
	setPosition(widok.getCenter().x + 300, widok.getCenter().y - 500);
	update(); 
	tekst->setPosition(getPosition().x + 30,getPosition().y + 50);
	tekst->setString(std::to_string(player.return_score()));
}

void coin_counter::draw(sf::RenderWindow* window)
{
	window->draw(*this);
	window->draw(*tekst); 
}
