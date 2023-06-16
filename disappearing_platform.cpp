#include "disappearing_platform.h"
disappearing_platform::disappearing_platform(sf::Vector2f switch_speed2 , sf::Vector2f size, sf::Vector2f position) : platform(size, position)
{
	switch_speed = switch_speed2; 
	pozycja = position; 
	setFillColor(sf::Color( std::round(255 - abs(position.y) / 60),0, std::round(255 - abs(position.y) / 60), 255)); 
	offset = rand() % 20 / 20; 
	clock.restart(); 
}

disappearing_platform::~disappearing_platform()
{
	
}

void disappearing_platform::update() // platforma znika w okreslonych interwalach , na okreslony czas , oraz z okreslonym przesunieciem pierwotnym
{
	if (czas.asSeconds() == offset)
	{
		clock.restart(); 
		offset = 2000; // ustawiamy wartosc ktorej nigdy nie osiagnie , poniewaz platformy sa juz rozstrojone od siebie 
	}
	czas = clock.getElapsedTime(); 
	if (czas.asSeconds() > switch_speed.x)
	{
		if(getPosition().x > 0)
		move(-5000,0); 
		if (czas.asSeconds() > switch_speed.x + switch_speed.y)
		{
			move(5000,0); 
			clock.restart(); 
		}
	}
	
}

