#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
class platform  : public sf::RectangleShape
{
public:
	platform(sf::Vector2f size, sf::Vector2f position);
	sf::FloatRect return_global_bounds(); 
	virtual void update();
	virtual sf::Vector2f return_speed(); 
	void rusz(sf::Vector2f speed);
	~platform(); 
private:
	
	sf::Texture tekstura;
	sf::Sprite sprite;
};
