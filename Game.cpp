#include "Game.h"
#include "player.h"
#include "coin.h"
#include"MainMenu.h"
Game::Game()
{
	std::cout << "Witamy w cloud TOWER!" << std::endl; 
	std::cout << "Wykonali :" << std::endl; 
	std::cout << "Aby zaczac wcisnij dowolny przycisk :-)" << std::endl;
}

void Game::play()
{
	background.ready_background_texture();
	ready_game();
	MainMenu menu;
	player player(1, sf::Vector2f(2050, 790)); //tworzenie gracza 
	menu.PlayMainMenu(window);
	sf::RenderWindow window3(sf::VideoMode(600, 400), "SFML works!");
	while (window->isOpen())
	{ 
		sf::Vector2f play_pos = player.getPosition(); 

		generate_platform(player); // sprawdzanie pozycji platform , nastepnie generowanie lub usuwanie zbednych platform
		generate_bombs(player); // to samo tylko z bombami 
		close_window(window); // zamykanie okna 
		pauza(window,player); // pauzuje gre 
		window->clear(sf::Color::Black); // czyszcenie ekranu 
		background.draw_tlo(window); // rysowanie tla
		update_all( window , player); // updatowanie pozycji platform oraz bomb nastepnie rysowanie ich	
		update_coin_count(); 
        draw_all(window); // rysowanie wszystkich obiektow poza graczem 
		move_bombs(); 
		player.update(window, platformy, bomby , monety); // update gracza na podstawie pozycji platform i innych rzeczy nastepnie rysowanie go 
		update_view(window, player);
		if (player.get_status() == player::dead) // sprawdzanie warunku konca gry  , sam status dead czy alive jest aktualizowany w funkcji update
		{
			death(player , window); //jezeli gracz jest 'dead' to funkcja konczy gre 
		}
		window3.clear(sf::Color::Black);
		window3.draw(*coin_count);
		window3.display(); 
		 	
	}
}

void Game::generate_platform(player player) 
{
	int los_monety = rand() % 4; 
	int los_kierunek = rand() % 3;
	int kierunek_ruchu = 1;
	if (los_kierunek == 1)
	{
		kierunek_ruchu = -1; 
	}
		if (platformy.size() < 14) 
		{
			int los = rand() % 6;
			if (los == 1 || los ==2)
			{ // platformy.emplace_back(new platform(sf::Vector2f(200, 50), sf::Vector2f(generate_rand_dist(), platformy.back()->getPosition().y - 200)));
				platformy.emplace_back(new platform(sf::Vector2f(200, 50), sf::Vector2f(platformy.back()->getPosition().x + (70 + rand() % 50)*kierunek_ruchu, platformy.back()->getPosition().y - 200)));
				if (los_monety == 3)
					monety->emplace_back(new coin(sf::Vector2f(platformy.back()->getPosition().x + rand() % 100, platformy.back()->getPosition().y - 50))); 
			}
			else if (los == 3 || los == 4)
			{
				platformy.emplace_back(new moving_platform(sf::Vector2f((rand() % 30) / 10 + 2, 0), sf::Vector2f(200, 50), sf::Vector2f(platformy.back()->getPosition().x + (70 + rand() % 50)*kierunek_ruchu, platformy.back()->getPosition().y - 200)));
				if (los_monety == 3)
				monety->emplace_back(new coin(sf::Vector2f(platformy.back()->getPosition().x + rand() % 100, platformy.back()->getPosition().y - 50)));
			}
			else if (los == 5)
			{
				platformy.emplace_back(new disappearing_platform(sf::Vector2f(3 + (rand() % 30) / 10, 1.2 - (rand() % 50) / 100), sf::Vector2f(200, 50), sf::Vector2f(platformy.back()->getPosition().x + (70 + rand() % 50)*kierunek_ruchu, platformy.back()->getPosition().y - 200)));
				if (los_monety == 3)
					monety->emplace_back(new coin(sf::Vector2f(platformy.back()->getPosition().x + rand() % 100, platformy.back()->getPosition().y - 50)));
			}
		}
		for (auto x : platformy)
		{
			if (x->getPosition().y  > player.getPosition().y + 800 ) 
			{
				auto element = std::find(platformy.begin(), platformy.end(), x);
				delete x; 
				platformy.erase(element); 
			}
		}
		if(monety->size()>0)
			for (auto m : *monety)
			{
				if (m->getPosition().y > player.getPosition().y + 400 && monety->size()>0)
				{
					auto element = std::find(monety->begin(), monety->end(), m);
					delete m; 
					monety->erase(element);
				}
			}
		
}


void Game::move_all(sf::Vector2f ruch)
{
	for (auto& p : platformy)
	{
		p->move(ruch); 
	}
	for (auto& m : *monety)
	{
		m->move(ruch); 
	}
}


void Game::next_screen(player &player) // funkcja rusza wszystkie elementy na ekranie w zaleznosci od wysokosci gracza 
{		
	if (player.getPosition().y < -1600 && map_number == 1 )
	{
		map_number = 2; 
		platformy.clear(); 
		player.setPosition(sf::Vector2f(player.getPosition().x, -3250));
		platformy.emplace_back(new platform(sf::Vector2f(200, 50), sf::Vector2f(player.getPosition().x-50, -3200)));
		//minimap->setPosition(sf::Vector2i(play.getPosition().x - 1000, minimap->getPosition().y));
		viev_minimap.setCenter(player.getPosition().x , player.getPosition().y -1500);
		minimap->setView(viev_minimap); 
	}
	if (player.getPosition().y < -6500 && map_number == 2)
	{
		map_number = 3; 
		platformy.clear();
		player.setPosition(sf::Vector2f(player.getPosition().x, -7450));
		platformy.emplace_back(new platform(sf::Vector2f(200, 50), sf::Vector2f(player.getPosition().x - 50, -7350)));
		viev_minimap.setCenter(player.getPosition().x, player.getPosition().y - 1350);
		
		
		minimap->setView(viev_minimap);
	}
	if (player.getPosition().y < -10000 && map_number == 3)
	{
		platformy.clear();
		bomby.clear();
		monety->clear(); 
		platformy.emplace_back(new platform(sf::Vector2f(200, 50), sf::Vector2f(2000, 900)));
		player.setPosition(2100,850);
		map_number = 1;
	}

}


void Game::ready_game() // przygotowanie gry , ladowanie grafik oraz ustalanie poczatkowych wartosci zmiennych
{
	//ready_background_texture(); 
	srand((unsigned)time(NULL));
	platformy.emplace_back(new platform(sf::Vector2f(200, 50), sf::Vector2f(2000, 900)));
	bomby.emplace_back(new bomb(sf::Vector2f(400, 20000)));
	game_speed = 0; 
	monety = new std::vector<coin*>; 
	window = new sf::RenderWindow(sf::VideoMode(800, 1000), "Cloud tower",sf::Style::None); // tworzenie okna  
	minimap = new sf::RenderWindow(sf::VideoMode(500, 700), "MiniMap" , sf::Style::None);
	view_game = sf::View(sf::FloatRect(650, 790, 800.0f, 1000.0f));
	viev_minimap = sf::View(sf::FloatRect(1000, -2100, 2428, 3400));
	//viev_minimap = sf::View(sf::FloatRect(1500, -2000, 2000, 3000));
	//view_game.setCenter(650, 790);
	coin_count = new coin(sf::Vector2f(2200, 700)); 
	coin_count->setScale(4, 4); 
	window->setFramerateLimit(60);
	minimap->setView(viev_minimap);
	minimap->setFramerateLimit(60); 
	minimap->setPosition(sf::Vector2i(50,300)); 
	map_number = 1; 
	//ready_background_texture();
	background.draw_tlo(window);
	//monety->emplace_back(coin_count); 
	
	
}


void Game::draw_tlo(sf::RenderWindow*window) // rysowanie tla 
{
	window->draw(tlo_s);
    window->draw(tlo_s3);
    window->draw(tlo_s2);
}


float Game::generate_rand_dist() // generowanie pozycji X nastepnej platformy na podstawie pozycji poprzedniej 
{		                         // tak aby gracz byl w stanie doskoczyc do kazdej platformy 
	int dodatni = 1; 
	bool blokada = true; 
	float wynik = 0; ;
	while (blokada == true)
	{
		float random = rand() % 20;
		random = random / 10;
		if (rand() % 3 == 1)
		{
			dodatni = -1;
		}
		else 
		{
			dodatni = 1; 
		}
		wynik = dodatni * ( 120 + rand() % 200 ) ;
		if (wynik + platformy.back()->getPosition().x > 1 && wynik  +  platformy.back()->getPosition().x < 599)
		{
			return wynik + platformy.back()->getPosition().x; 
		}
	}
}


void Game::generate_bombs(player player) // tworzenie i usuwanie bomb
{
	bomb_time = bomb_clock.getElapsedTime(); 
	if (bomby.size() < 6 && bomb_time.asSeconds() > 1)
	{
		bomby.emplace_back(new bomb(sf::Vector2f(player.getPosition().x-500 + rand()%1000, player.getPosition().y - 1200)));
		bomb_clock.restart(); 
		std::cout << "tworze bombe " << std::endl;
	}
	if(bomby.size()>0)
	if (bomby.front()->getPosition().y > player.getPosition().y + 500)
	{
		delete bomby.front(); 
		bomby.erase(bomby.begin()); 
	}
}


void Game::update_all(sf::RenderWindow *window , player& play)
{
	for (auto& x : platformy) // updatowanie pozycji platform oraz rysowanie ich
	{
		x->update();
	}
	if (monety->size() > 0)
	for (auto& m : *monety)
	{
		m->update(); 
	}
	next_screen(play); // updatowanie pozycji bomb oraz platform 
}


void Game::draw_all(sf::RenderWindow*window)
{
	for (auto& x : platformy)
	{
		window->draw(*x); 
	}
	for (auto& x : bomby)
	{
		window->draw(*x);
	}	
	for (auto& m : *monety)
	{
		window->draw(*m);
	}
}



void Game::death(player& play, sf::RenderWindow*window) // ekran smierci 
{
	for (auto x : bomby)
	{
		if (play.getGlobalBounds().intersects(x->getGlobalBounds()))
		{
			sf::Clock zegar;
			x->move(sf::Vector2f(-100, 0));
			while (zegar.getElapsedTime().asSeconds() < 2)
			{
				window->clear(sf::Color::White);
				background.draw_tlo(window);
				draw_all(window);
				x->update(true, zegar);
				window->draw(*x);
				window->display();

			}
		}
	}
	system("CLS");
	std::cout << "Przegrales!" << std::endl;
	std::cout << "Wcisnij cokolwiek aby kontynuowac" << std::endl;
	std::cout << "Wynik gracza to: " <<play.return_score()<< std::endl;
	GameOver(play);
	//std::cin.get();
	//window->close();
}


void Game::pauza(sf::RenderWindow*window, player& gracz)
{
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) // dodany element pauzy , gdy gracz jest w powietrzu 
	{
		// wywolujemy element klasy pauza ktory pobiera okno oraz rysuje swoje elementy na to
		// zaokraglamy pozycje elementow do liczb calkowtych aby elementy nie "skakaly" po ekranie 
		window->clear(); // nastepnie rysujemy nowa klatke , po czym przekazujemy tak narysowane okno do funkcji "Play"; 
		//background.draw_tlo(window);
        MainMenu menu;
		for (auto x : platformy)
		{
			x->setPosition(std::round(x->getPosition().x), std::round(x->getPosition().y));
		}
		menu.PlayPauseMenu(window,gracz); 
		draw_all(window);
		window->draw(gracz);
		window->display();
		std::cout << "Zapauzowano!" << std::endl;
		//pause.Play(window);
		clock.restart();



	}
}



void Game::move_bombs()
{
	for (auto& x : bomby) // bomby 
	{
		x->move(sf::Vector2f(0, 2.5));
	}
}


void Game::ready_background_texture()
{
	if (!tlo1.loadFromFile("assets/winter 8/hd.png"))
	{
		std::cout << "nie zaladowano tla";
	}
	tlo_s.setTexture(tlo1);
	tlo_s.setScale(3, 3);
	tlo_s.setPosition(-1000, -3500);
	if (!tlo2.loadFromFile("assets/winter 7/hd.png"))
	{
		std::cout << "nie zaladowano tla";
	}
	tlo_s2.setTexture(tlo2);
	tlo_s2.setPosition(sf::Vector2f(-1000, -7000));
	tlo_s2.setScale(sf::Vector2f(3, 3));
	if (!tlo3.loadFromFile("assets/winter 4/hd.png"))
	{
		std::cout << "nie zaladowano tla";
	}
	tlo_s3.setTexture(tlo3);
	tlo_s3.setPosition(sf::Vector2f(-1000, -10500));
	tlo_s3.setScale(sf::Vector2f(3, 3));
	if (!tlo4.loadFromFile("assets/parallax-mountain-trees.png"))
	{
		std::cout << "nie zaladowano tla";
	}
	tlo_s4.setTexture(tlo4);
	tlo_s4.setPosition(sf::Vector2f(0-1000, 4000-9000));
	tlo_s4.setScale(sf::Vector2f(3, 3));
	if (!tlo5.loadFromFile("assets/parallax-mountain-mountains.png"))
	{
		std::cout << "nie zaladowano tla";
	}
	tlo_s5.setTexture(tlo5);
	tlo_s5.setPosition(sf::Vector2f(0-1000, 0-9000));
	tlo_s5.setScale(sf::Vector2f(3, 3));
}

void Game::update_minimap(player play )
{
	minimap->clear(sf::Color::Blue);
	background.draw_tlo(minimap); 
	draw_all(minimap);
	minimap->draw(play); 
	//minimap->draw(*coin_count); 
	minimap->display(); 
}

void Game::zapis(player& play,std::string nick)
{
	std::fstream zapis;
	zapis.open("Wyniki.csv", std::ios::app);
	zapis << play.return_score() << ',' << nick << std::endl;
	zapis.close();
}

void Game::GameOver(player& gracz)
{
	sf::RenderWindow window2(sf::VideoMode(600, 400), "SFML works!", sf::Style::None);
	sf::Font font1;
	std::string wynik = std::to_string(gracz.return_score());
	font1.loadFromFile("./assets/BigSmoke.ttf");
	sf::Texture background;
	background.loadFromFile("./assets/winter 1/1.png");
	sf::Sprite sprite;
	sprite.setTexture(background);
	sprite.setScale(3, 3);

	sf::Text t[5];
	t[0].setString("Game over");
	t[0].setCharacterSize(50);
	t[0].setFillColor(sf::Color::Black);
	t[0].setPosition(170, 30);
	t[0].setFont(font1);

	t[1].setString("Twoj wynik");
	t[1].setCharacterSize(30);
	t[1].setFillColor(sf::Color::Black);
	t[1].setPosition(150, 125);
	t[1].setFont(font1);

	t[2].setString(wynik);
	t[2].setCharacterSize(30);
	t[2].setFillColor(sf::Color::Black);
	t[2].setPosition(450, 125);
	t[2].setFont(font1);

	t[3].setString("Podaj swoj nick i nacisnij enter aby wrocic do menu");
	t[3].setCharacterSize(20);
	t[3].setFillColor(sf::Color::Black);
	t[3].setPosition(50, 200);
	t[3].setFont(font1);

	t[4].setString("nick");
	t[4].setCharacterSize(30);
	t[4].setFillColor(sf::Color::Black);
	t[4].setPosition(150, 300);
	t[4].setFont(font1);



	std::string input_text;
	sf::Text text("", font1);
	sf::Clock clock;

	

	
	while (window2.isOpen())
	{
		sf::Event event2;
		while (window2.pollEvent(event2))
		{
			if (event2.type == sf::Event::Closed)
				window2.close();
			else if (event2.type == sf::Event::TextEntered)
			{
				if (std::isprint(event2.text.unicode) && input_text.size() < 10)
					input_text += event2.text.unicode;
			}
			else if (event2.type == sf::Event::KeyReleased) {
				if (event2.key.code == sf::Keyboard::BackSpace) {
					if (!input_text.empty())
						input_text.pop_back();
				}
				if (event2.key.code == sf::Keyboard::Enter) {
					window2.close();
					zapis(gracz,input_text);
					window->close();
					minimap->close();
					gracz.alive;
					Game gra;			
					gra.play();
					
				}
			}
		}
		static sf::Time text_effect_time;
		static bool show_cursor;

		text_effect_time += clock.restart();

		if (text_effect_time >= sf::seconds(0.5f))
		{
			show_cursor = !show_cursor;
			text_effect_time = sf::Time::Zero;
		}

		text.setString(input_text + (show_cursor ? '_' : ' '));
		text.setPosition(350, 300);
		text.setFillColor(sf::Color::Black);


		window2.clear();
		window2.draw(sprite);
		for (int i = 0; i < 5; i++)
		{
			window2.draw(t[i]);
		}
		window2.draw(text);
		window2.display();
	}
}

void Game::close_window(sf::RenderWindow *window)
{
	while (window->pollEvent(event)) // zamkniecie okna 
	{
		if (event.type == sf::Event::Closed)
			window->close();
	}
}

void Game::update_view(sf::RenderWindow* window , player player)
{
	view_game.setCenter(player.getPosition());
	window->setView(view_game);
	window->display(); // wyswietlanie klatki gry
	update_minimap(player);
}

void Game::update_coin_count()
{
	coin_count->setPosition(view_game.getCenter().x + 100, view_game.getCenter().x - 100); 
}
