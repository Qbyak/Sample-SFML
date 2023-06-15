#include "bomb.h"

bomb::bomb(sf::Vector2f pos)
{
	if (!tekstura_wybuch.loadFromFile("assets/Explosion.png")) // szykowane tekstury wybuchu
	{
		std::cout << "Nie za³adowano  tekstury wybuchu" << std::endl;
	}
	if (!tekstura.loadFromFile("assets/bomb.png")) // szykowanie teksruty bomby
	{
		std::cout << "Nie za³adowano grafiki bomby" << std::endl;
	}
	setPosition(pos); 
	setTexture(tekstura);
	setScale(0.5, 0.5); 
	klatki_animacji.emplace_back(sf::IntRect(30, 20, 40, 100));
	for (int i = 0; i < 10; i++)
	{
		klatki_animacji.emplace_back(sf::IntRect(80 + 100 * i, 20, 90, 120));
	}
	numer_klatki_animacji = 0; 
}

bomb::~bomb()
{	
}

bool bomb::update()
{
		setTexture(tekstura_wybuch);
		setScale(sf::Vector2f(2, 2)); 
		animate_boom(clock);
		if (clock.getElapsedTime().asSeconds() > 4)
			return false;
		else
			return true;	
}

void bomb::reset_clock()
{
	clock.restart(); 
}

void bomb::animate_boom(sf::Clock clock) // animacja wybuchu 
{
	if (clock.getElapsedTime().asSeconds() > czas_animacji.asSeconds() + 0.2 && czas_animacji.asSeconds() < 2)
	{
		numer_klatki_animacji++;
		czas_animacji = clock.getElapsedTime();
	}
	setTextureRect(klatki_animacji[numer_klatki_animacji]);
}
