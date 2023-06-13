#include "bomb.h"

bomb::bomb(sf::Vector2f pos)
{
	if (!tekstura_wybuch.loadFromFile("assets/Explosion.png"))
	{
		std::cout << "Nie za³adowano  tekstury wybuchu" << std::endl;
	}
	if (!tekstura.loadFromFile("assets/bomb.png"))
	{
		std::cout << "Nie za³adowano grafiki bomby" << std::endl;
	}
	else
	{
		std::cout << "Tworze bombe" << std::endl; 
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
	std::cout << "Usuwam bombe" << std::endl; 
	
	
}

bool bomb::update()
{
	
	  // if(getTexture() != tekstura_wybuch)
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
	if (clock.getElapsedTime().asSeconds() > czas_animacji.asSeconds() + 0.2 &&  czas_animacji.asSeconds() < 2)
	{
		numer_klatki_animacji++;
		czas_animacji = clock.getElapsedTime();
	}
	/*if (czas_animacji.asSeconds() > 2.8)
	{
		clock.restart();
		czas_animacji = clock.getElapsedTime();
		numer_klatki_animacji = 0;
	}*/
	setTextureRect(klatki_animacji[numer_klatki_animacji]);
		/*czas = clock.getElapsedTime();
		if (czas.asSeconds() < 0.1)
			setTextureRect(sf::IntRect(30, 20, 40, 100));		
		else if (czas.asSeconds() < 0.2)
			setTextureRect(sf::IntRect(80, 20, 100, 120));
		else if (czas.asSeconds() < 0.4)
			setTextureRect(sf::IntRect(180, 20, 100, 120));
		else if (czas.asSeconds() < 0.6)
			setTextureRect(sf::IntRect(280, 20, 100, 120));
		else if (czas.asSeconds() < 0.8)
			setTextureRect(sf::IntRect(380, 00, 100, 120));
		else if (czas.asSeconds() < 1)
			setTextureRect(sf::IntRect(480, 00, 100, 120));
		else if (czas.asSeconds() < 1.2)
			setTextureRect(sf::IntRect(580, 00, 90, 120));
		else if (czas.asSeconds() < 1.4)
			setTextureRect(sf::IntRect(680, 00, 90, 120));
		else if (czas.asSeconds() < 1.6)
			setTextureRect(sf::IntRect(780, 00, 90, 120));
		else if (czas.asSeconds() < 1.8)
			setTextureRect(sf::IntRect(880, 00, 90, 120));
		else if (czas.asSeconds() < 2)
			setTextureRect(sf::IntRect(980, 00, 90, 120));*/
}
