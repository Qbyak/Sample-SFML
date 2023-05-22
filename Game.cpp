#include "Game.h"
#include "player.h"
#include <vector>
Game::Game()
{
	std::cout << "Witamy w cloud TOWER!" << std::endl; 
	std::cout << "Wykonali :" << std::endl; 
	std::cout << "Aby zaczac wcisnij dowolny przycisk :-)" << std::endl;
	
}

void Game::play()
{
	ready_game(); 
    player play(1, sf::Vector2f(650, 800)); 
    sf::RenderWindow window(sf::VideoMode(800, 1000), "Cloud tower");
	window.setFramerateLimit(60);	
	sf::Clock clock;
	while (window.isOpen())
	{ 
		sf::Time elapsed = clock.restart();
		generate_platform(); // sprawdzanie pozycji platform , nastepnie generowanie lub usuwanie zbednych platform
		while (window.pollEvent(event)) // zamkniecie okna 
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear(sf::Color::Red);
		draw_tlo(window); 
		for (auto& x : platformy) // updatowanie pozycji platform oraz rysowanie ich
		{
			x->update(); 
			window.draw(*x);
		}  
		play.update(window , platformy); // update gracza na podstawie pozycji platform i innych rzeczy
		next_screen(play,elapsed); // jezeli gracz przekroczyl dana wysokosc , zaladowac kolejny ekrean 
		window.display(); 
		if (play.if_przegrana() == true)
		{
			system("CLS");
			//for(int i = 0  ; i <1000 ; i++) // dla zartu 
			std::cout << "Przegrales!" << std::endl; 
			std::cout << "Wcisnij cokolwiek aby kontynuowac" << std::endl; 
			std::cin.get();
			window.close();
		}
	}
}
void Game::generate_platform()
{    
	
	if (platformy.size() < 8)
	{ 
		int los = rand() % 3 ;
		if (los == 1)
		{    // generate_rand_dist() // rand()%700
			platformy.emplace_back(new platform(sf::Vector2f(200, 50), sf::Vector2f(generate_rand_dist(), platformy.back()->getPosition().y - 200)));
		}
		else if (los==2)
		platformy.emplace_back(new moving_platform(sf::Vector2f((rand()%30 )/10 , 0), sf::Vector2f(200, 50), sf::Vector2f(generate_rand_dist(), platformy.back()->getPosition().y - 200)));
	}
	if (platformy.front()->getPosition().y > 1000)
	{

		delete platformy.front(); 
		platformy.erase(platformy.begin()); 
	}
}

void Game::move_all(sf::Vector2f ruch)
{
	for (auto& p : platformy)
	{
		p->move(ruch); 
	}
}

void Game::add_score(player& play)
{
	
	score++;
	system("CLS");
	std::cout << "wynik gracza to: " << score << std::endl;
}

void Game::next_screen(player &play, const sf::Time& elapsed)
{
	move_all(sf::Vector2f(0 * elapsed.asMilliseconds(), 0.02 * elapsed.asMilliseconds()));
	play.move(sf::Vector2f(0 * elapsed.asMilliseconds(), 0.02 * elapsed.asMilliseconds()));
	while (play.getPosition().y < 300)
	{
		
		move_all(sf::Vector2f(0*elapsed.asMilliseconds(), 1 * elapsed.asMilliseconds()));
		play.move(sf::Vector2f(0 * elapsed.asMilliseconds(), 1 * elapsed.asMilliseconds()));
		//add_score(play);
	}
}

void Game::ready_game()
{
	if (!tlo1.loadFromFile("assets/parallax-mountain-bg.png"))
	{
		std::cout << "nie zaladowano tla";
	}
	tlo_s.setTexture(tlo1);
	tlo_s.setScale(3, 5);
	tlo_s.setPosition(0, 0); 
	if (!tlo2.loadFromFile("assets/parallax-mountain-foreground-trees.png"))
	{
		std::cout << "nie zaladowano tla";
	}
	tlo_s2.setTexture(tlo2); 
	tlo_s2.setPosition(sf::Vector2f(0, 350));
	tlo_s2.setScale(sf::Vector2f(4,4)); 
	if (!tlo3.loadFromFile("assets/parallax-mountain-montain-far.png"))
	{
		std::cout << "nie zaladowano tla";
	}
	tlo_s3.setTexture(tlo3);
	tlo_s3.setPosition(sf::Vector2f(0, -100));
	tlo_s3.setScale(sf::Vector2f(4, 7));
	if (!tlo4.loadFromFile("assets/parallax-mountain-trees.png"))
	{
		std::cout << "nie zaladowano tla";
	}
	tlo_s4.setTexture(tlo4);
	tlo_s4.setPosition(sf::Vector2f(0, 400));
	tlo_s4.setScale(sf::Vector2f(2, 4));
	if (!tlo5.loadFromFile("assets/parallax-mountain-mountains.png"))
	{
		std::cout << "nie zaladowano tla";
	}
	tlo_s5.setTexture(tlo5);
	tlo_s5.setPosition(sf::Vector2f(0, 0));
	tlo_s5.setScale(sf::Vector2f(6, 6));
	srand((unsigned)time(NULL));
	platformy.emplace_back(new platform(sf::Vector2f(200, 50), sf::Vector2f(600, 900)));
	//max_y = play.getPosition().y;
	
	
}

void Game::draw_tlo(sf::RenderWindow& window)
{
	window.draw(tlo_s);
	window.draw(tlo_s5); 
	window.draw(tlo_s3);
	window.draw(tlo_s4); 
    window.draw(tlo_s2);
}

float Game::generate_rand_dist()
{		
	int dodatni = 1; 
	bool blokada = true; 
	float wynik = 0; ;
	while (blokada == true)
	{
		float random = rand() % 20;
		random = random / 10;
		std::cout << random << std::endl;
		if (rand() % 3 == 1)
		{
			dodatni = -1;
			//std::cout << "jestem ujemny" << std::endl; 
		}
		else 
		{
			dodatni = 1; 
		}
		wynik = dodatni * ( 120 + rand() % 200 ) ;
		std::cout << wynik + platformy.back()->getPosition().x << std::endl;
		if (wynik + platformy.back()->getPosition().x > 1 && wynik  +  platformy.back()->getPosition().x < 599)
		{
			//std::cout << "jestem tutaj" << std::endl; 
			return wynik + platformy.back()->getPosition().x; 
		}
		else
		{
		}
		//std::cout << wynik + platformy.back()->getPosition().x << std::endl; 
	}
	// return 0.0f;
}
