#include "player.h"
#include "Game.h"
player::player(int klasa_gracza, sf::Vector2f pos) 
{
	if (klasa_gracza == 1)
	{
		if (!klasa.loadFromFile("assets/character.png"))
		{
			std::cout << "Nie za³adowano grafiki gracza" << std::endl;
		}
	}
	setPosition(pos);
	setTexture(klasa);
	setScale(2, 2);
	setTextureRect(sf::IntRect(110, 0, 30, 37));
	grawitacja = sf::Vector2f(0, 0.3); 
	przegrana = false; 
}

sf::Vector2f player::sprawdz_klaw()
{
	sf::Vector2f predkosc(0, 0);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		predkosc.x = -2;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		predkosc.x = 2;
	}
	return predkosc;
}

void player::draw(sf::RenderWindow& okno)
{
	okno.draw(*this);
}

void player::update(sf::RenderWindow& okno , std::vector<platform*> platformy)
{    //  // sprawdzilismy w funckji collision czy kolizja wystepuje z ruchom¹ platforma. jezeli tak to move_platforma jest rozna od zera a za razem gracz "jedzie" z platforma
	pozycja = getPosition(); 
	move(sprawdz_klaw()) ;// ruch jest rozpatrywany osobno w plaszczyznie x oraz y , tutaj jest plaszczyzna X 
	move(move_platform); 
	if (collision(platformy, true) == true) // najpierw ruszamy w plaszyznie x , sprawdzamy kolizje. jezeli wystapila to cofamy obiekt
	{                                       // do momentu przed kolizja 
		setPosition(pozycja); 
		
	}	
	pozycja = getPosition();
	if (v_gracz.y < 8)
	{
		v_gracz += grawitacja; 
	}
	move(v_gracz);// tutaj to samo tylko dla osi y 
	move(move_platform); 

	if (collision(platformy, false ) == true) 
	{
		setPosition(pozycja);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			v_gracz.y -= 22;
		}
	}
	else
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			v_gracz.y -= 0.4;
			std::cin.get();
		}
	}
	v_gracz.x = 0; 
	draw(okno);
}

/*bool player::collision(std::vector<platform*> platformy, bool blokada)
{
	move_platform = sf::Vector2f(0, 0); 
	bool kolizja = false; 
	if ( getGlobalBounds().left <= 0 || getGlobalBounds().left + getGlobalBounds().width >= 800)
	{
		kolizja = true;
	}
	for (auto platforma : platformy)
	{
		if (getGlobalBounds().intersects(platforma->getGlobalBounds()))
		{
			move_platform = platforma->return_speed();
			kolizja = true;
			if (getGlobalBounds().top >= platforma->getGlobalBounds().top - platforma->getGlobalBounds().height && blokada == false)
			{
				v_gracz.y = 0; 
			}			
		}
	}
	return kolizja;
}*/
bool player::collision(std::vector<platform*> platformy, bool blokada)
{
	move_platform = sf::Vector2f(0, 0); 
	bool kolizja = false; 
	for (auto platforma : platformy)
	{
		//std::cout << v_gracz.y << std::endl;
		
		
		 if (getGlobalBounds().intersects(platforma->getGlobalBounds()) && v_gracz.y >= 0 && getGlobalBounds().top + getGlobalBounds().height - 19*grawitacja.y - 4 <= platforma->getGlobalBounds().top)
		{
			move_platform = platforma->return_speed();
			kolizja = true;	
		}
		 else if (getGlobalBounds().intersects(platforma->getGlobalBounds()) && v_gracz.y < 0)
		 {
			 move(0, -0.1);
		 }
		
	}
	return kolizja; 
}


sf::Vector2f player::move_y()
{
	sf::Vector2f zwracane = v_gracz + move_platform;
	return sf::Vector2f();
}

bool player::if_przegrana()
{   
	if (getGlobalBounds().top + getGlobalBounds().height >= 1000)
	{
		return true;
	}
	else
		return false; 
}
