#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
class heart : public sf::Sprite
{
public:
	heart(sf::Vector2f pozycja , sf::Vector2f skala); // konstruktow
	~heart();
private:
	sf::Texture tekstura; // teksutra 
};
