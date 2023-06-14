#include "heart.h"

heart::heart(sf::Vector2f pozycja , sf::Vector2f skala)
{
	setPosition(pozycja);
	if (!tekstura.loadFromFile("assets/heart pixel art 64x64.png"))
	{
		std::cout << "Nie załadowano grafiki serca" << std::endl;
	}
	else
	{
		setTexture(tekstura); 
		setScale(skala.x , skala.y); 
	}
}

heart::~heart()
{
}
