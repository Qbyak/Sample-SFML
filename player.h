#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "platform.h"
#include "moving_platform.h"
class player : public sf::Sprite 
{
public:
	player(int klasa, sf::Vector2f pos); 		
	void update(sf::RenderWindow& okno , std::vector<platform*> platformy);
	//void rusz(sf::Vector2f speed); 
	sf::Vector2f move_y(); 
    bool if_przegrana();
private:
	bool collision(std::vector<platform*> platformy, bool blokada);
	sf::Vector2f sprawdz_klaw();
	void draw(sf::RenderWindow& okno);	
private:
	sf::Vector2f v_gracz;
	sf::Vector2f grawitacja;
	sf::Vector2f pozycja; 
	sf::Vector2f move_platform; 
	sf::Sprite gracz; 
	sf::Texture klasa;
	bool przegrana; 
};

