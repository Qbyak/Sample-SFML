#include "coin.h"

coin::coin(sf::Vector2f pozycja = sf::Vector2f(0,0)) // inicjalizacja elementow
{
	if (!tekstura.loadFromFile("assets/coin_gold.png"))
	{
		std::cout << "Nie za³adowano grafiki monety" << std::endl;
	}
	setTexture(tekstura); 
	setTextureRect(sf::IntRect(96, 0, 32, 20)); 
	setPosition(pozycja); 
	setScale(2, 2); 
	numer_klatki_animacji = 0; 
	for (int i = 0; i < 8; i++)
	{
		klatki_animacji.emplace_back(sf::IntRect(0 + 32 * i, 0, 32, 20)); 
	}
}

coin::~coin()
{
}

void coin::update() // funkcja update wywolujaca animacje 
{
	this->animate(); 
}

void coin::animate() // animacja na podstawie uplynietego czasu 
{
	if (clock.getElapsedTime().asSeconds() > czas_animacji.asSeconds() + 0.15)
	{
		numer_klatki_animacji++; 
		czas_animacji = clock.getElapsedTime(); 
	}
	if (czas_animacji.asSeconds() > 1.2)
	{
		clock.restart();
		czas_animacji = clock.getElapsedTime(); 
		numer_klatki_animacji = 0; 
	}
	setTextureRect(klatki_animacji[numer_klatki_animacji]);
}
