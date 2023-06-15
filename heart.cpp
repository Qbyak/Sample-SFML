#include "heart.h"

heart::heart(sf::Vector2f pozycja , sf::Vector2f skala) // inicjalizacja obiektow 
{
	setPosition(pozycja);
	if (!tekstura.loadFromFile("assets/heart pixel art 64x64.png"))
	{
		std::cout << "Nie za³adowano grafiki serca" << std::endl;
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
