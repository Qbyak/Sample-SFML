#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "platform.h"
#include "moving_platform.h"
class bomb : public sf::Sprite
{
public:
	bomb(sf::Vector2f pos); 
	~bomb(); 
    //funkcje 
	bool update(); //wywo³anie wybuchu
	void reset_clock();//reset zegara 
private:
	void animate_boom(sf::Clock clock); // animcja wybuchu 
private:
	//tekstury 
	sf::Texture tekstura;
	sf::Texture tekstura_wybuch; 
	sf::Sprite sprite; 
	//zmienne do animacji 
	int numer_klatki_animacji;
	sf::Time czas_animacji;
	sf::Clock collision_clock;
	std::vector <sf::IntRect> klatki_animacji; 
	sf::Clock clock;

};

