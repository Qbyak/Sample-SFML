#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
class platform  : public sf::RectangleShape
{
public:
	platform(sf::Vector2f size, sf::Vector2f position);//konstruktor platformy standardowej
	~platform();

	//funkcje
	virtual void update();//
	virtual sf::Vector2f return_speed(); //zwracanie predkosci poruszania sie platformy, dla zwyklej v=0,0
	void rusz(sf::Vector2f speed);
private:
	//teksutry
	sf::Texture tekstura;
	sf::Sprite sprite;
};
