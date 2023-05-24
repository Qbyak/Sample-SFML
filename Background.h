#pragma once
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
class Background
{
public:
	void ready_game();
	void draw_tlo(sf::RenderWindow& window);
protected:
	sf::Texture tlo1;
	sf::Texture tlo2;
	sf::Texture tlo3;
	sf::Texture tlo4;
	sf::Texture tlo5;
	sf::Event event;
	sf::Sprite tlo_s;
	sf::Sprite tlo_s2;
	sf::Sprite tlo_s3;
	sf::Sprite tlo_s4;
	sf::Sprite tlo_s5;
};

