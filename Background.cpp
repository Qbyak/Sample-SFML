#include "Background.h"

void Background::draw_tlo(sf::RenderWindow* window) // rysowanie tla 
{
	window->draw(tlo_s);
	window->draw(tlo_s5);
	window->draw(tlo_s3);
	window->draw(tlo_s4);
	window->draw(tlo_s2);
}
void Background::draw_menu_background(sf::RenderWindow* window) // rysowanie tla menu
{
	tlo_s.setScale(sf::Vector2f(1, 1));
	tlo_s.setPosition(1, 1);
	window->draw(tlo_s);
}
void Background::draw_pause_background(sf::RenderWindow* window,player& play) // rysowanie tla pauzy
{
	tlo_s.setScale(sf::Vector2f(1, 1));
	tlo_s.setPosition(play.getPosition().x-2050, play.getPosition().y-500);
	sf::View view(sf::FloatRect(play.getPosition().x, play.getPosition().y, 800.0f, 1000.0f));
	window->setView(view);
	window->draw(tlo_s);
}
void Background::ready_background_texture() // przygotowanie tekstur 
{
		if(!tlo1.loadFromFile("assets/winter 8/hd.png"))
		{
			std::cout << "nie zaladowano tla";
		}
		tlo_s.setTexture(tlo1);
		tlo_s.setScale(sf::Vector2f(3, 3));
		tlo_s.setPosition(-1000, -3500);
		
		if(!tlo2.loadFromFile("assets/winter 7/hd.png"))
		{
			std::cout << "nie zaladowano tla";
		}
		tlo_s2.setTexture(tlo2);
		tlo_s2.setPosition(sf::Vector2f(-1000, -7000));
		tlo_s2.setScale(sf::Vector2f(3, 3));
		if(!tlo3.loadFromFile("assets/winter 4/hd.png"))
		{
			std::cout << "nie zaladowano tla";
		}
		tlo_s3.setTexture(tlo3);
		tlo_s3.setPosition(sf::Vector2f(-1000, -10500));
		tlo_s3.setScale(sf::Vector2f(3, 3));
		if(!tlo4.loadFromFile("assets/winter 1/hd.png"))
		{
			std::cout << "nie zaladowano tla";
		}
		tlo_s4.setTexture(tlo4);
		tlo_s4.setPosition(sf::Vector2f(0 - 1000, 4000 - 9000));
		tlo_s4.setScale(sf::Vector2f(3, 3));
		if(!tlo5.loadFromFile("assets/winter 2/hd.png"))
		{
			std::cout << "nie zaladowano tla";
		}
		tlo_s5.setTexture(tlo5);
		tlo_s5.setPosition(sf::Vector2f(0 - 1000, 0 - 9000));
		tlo_s5.setScale(sf::Vector2f(3, 3));

}
