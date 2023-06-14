#include "Game.h"
Game::Game()
{
	background.ready_background_texture();
	ready_game();
}

void Game::play()
{
	menu.PlayMainMenu(window); // wyswietla menu gry 
	while (window->isOpen()) // Glowna petla gry 
	{ 		
		close_window(window); // zamykanie okna 
		pauza(window,gracz); // pauzuje gre 
		window->clear(sf::Color::Black); // czyszcenie ekranu 
		update_all(window , gracz); // updatowanie wszystkich obiektow
        draw_all(window , gracz , true , true); // rysowanie wszystkich obiektow
		if (gracz.get_status() == player::dead) // sprawdzanie warunku konca gry  , sam status dead czy alive jest aktualizowany w funkcji update gracza
		{
			death(gracz, window); //jezeli gracz jest 'dead' to funkcja konczy gre 
		} 
		window->display(); // wyswietlanie klatki gry
	}
}

void Game::generate_platform(player player) // generowanie platform na podstawie funkcji rand() oraz pozycji innych platform 
{
	int los_monety = rand() % 4; 
	int los_kierunek = rand() % 2;
	int kierunek_ruchu = 1;
	if (los_kierunek == 1)
	{
		kierunek_ruchu = -1; 
	}
	if (platformy->size() == 0)
	{
		platformy->emplace_back(new platform(sf::Vector2f(200, 50), sf::Vector2f(0, 0)));
	}
		if (platformy->size() < 14)  
		{
			int los = rand() % 6;
			if (los == 1 || los ==2)
			{ // platformy->emplace_back(new platform(sf::Vector2f(200, 50), sf::Vector2f(generate_rand_dist(), platformy->back()->getPosition().y - 200)));
				platformy->emplace_back(new platform(sf::Vector2f(200, 50), sf::Vector2f(platformy->back()->getPosition().x + (70 + rand() % 50)*kierunek_ruchu, platformy->back()->getPosition().y - 200)));
				if (los_monety == 3)
					monety->emplace_back(new coin(sf::Vector2f(platformy->back()->getPosition().x + rand() % 100, platformy->back()->getPosition().y - 50))); 
			    if (rand() % 20 == 5)   // pseudo-losowa szansa na pojawienie sie serca
					serca->emplace_back(new heart(sf::Vector2f(platformy->back()->getPosition().x + 50 , platformy->back()->getPosition().y - 50), sf::Vector2f(0.5, 0.5)));
			}
			else if (los == 3 || los == 4)
			{
				platformy->emplace_back(new moving_platform(sf::Vector2f((rand() % 30) / 10 + 2, 0), sf::Vector2f(200, 50), sf::Vector2f(platformy->back()->getPosition().x + (70 + rand() % 50)*kierunek_ruchu, platformy->back()->getPosition().y - 200)));
				if (los_monety == 3)
				monety->emplace_back(new coin(sf::Vector2f(platformy->back()->getPosition().x + rand() % 100, platformy->back()->getPosition().y - 50)));
				if (rand() % 20 == 5)
					serca->emplace_back(new heart(sf::Vector2f(platformy->back()->getPosition().x + 50, platformy->back()->getPosition().y - 50), sf::Vector2f(0.5, 0.5)));
			}
			else if (los == 5)
			{
				platformy->emplace_back(new disappearing_platform(sf::Vector2f(3 + (rand() % 30) / 10, 1.2 - (rand() % 50) / 100), sf::Vector2f(200, 50), sf::Vector2f(platformy->back()->getPosition().x + (70 + rand() % 50)*kierunek_ruchu, platformy->back()->getPosition().y - 200)));
				if (los_monety == 3)
					monety->emplace_back(new coin(sf::Vector2f(platformy->back()->getPosition().x + rand() % 100, platformy->back()->getPosition().y - 50)));
				if (rand() % 20 == 5)
					serca->emplace_back(new heart(sf::Vector2f(platformy->back()->getPosition().x + 50, platformy->back()->getPosition().y - 50), sf::Vector2f(0.5, 0.5)));
			}
		}
		for (auto x : *platformy)
		{
			if (x->getPosition().y  > player.getPosition().y + 800 ) 
			{
				auto element = std::find(platformy->begin(), platformy->end(), x);

					delete x;
					platformy->erase(element);
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
		if (serca->size() > 0)
		{
			for (auto s : *serca)
			{
				if (s->getPosition().y > player.getPosition().y + 700)
				{
					auto element = std::find(serca->begin(), serca->end(), s);
					delete s;
					serca->erase(element); 
				}
			}
		}
		
}

void Game::move_all(sf::Vector2f ruch)
{
	for (auto& p : *platformy)
	{
		p->move(ruch); 
	}
	for (auto& m : *monety)
	{
		m->move(ruch); 
	}
}

void Game::next_screen(player &player) // zmiana map gry 
{		
	if (player.getPosition().y < -1600 && map_number == 1 )
	{
		map_number = 2; 
		platformy->clear(); 
		player.setPosition(sf::Vector2f(player.getPosition().x, -3300));
		platformy->emplace_back(new platform(sf::Vector2f(200, 50), sf::Vector2f(player.getPosition().x-50, -3200)));
		//minimap->setPosition(sf::Vector2i(play.getPosition().x - 1000, minimap->getPosition().y));
		viev_minimap.setCenter(player.getPosition().x , player.getPosition().y -1500);
		minimap->setView(viev_minimap); 
	}
	if (player.getPosition().y < -6500 && map_number == 2)
	{
		map_number = 3; 
		platformy->clear();
		player.setPosition(sf::Vector2f(player.getPosition().x, -7450));
		platformy->emplace_back(new platform(sf::Vector2f(200, 50), sf::Vector2f(player.getPosition().x - 50, -7350)));
		viev_minimap.setCenter(player.getPosition().x, player.getPosition().y - 1350);
		
		
		minimap->setView(viev_minimap);
	}
	if (player.getPosition().y < -10000 && map_number == 3)
	{
		platformy->clear();
		bomby->clear();
		monety->clear(); 
		platformy->emplace_back(new platform(sf::Vector2f(200, 50), sf::Vector2f(2000, 900)));
		player.setPosition(2100,800);
		viev_minimap.setCenter(player.getPosition().x, player.getPosition().y - 1350);
		minimap->setView(viev_minimap); 
		map_number = 1;
	}

}

void Game::ready_game() // przygotowanie gry , ladowanie grafik oraz ustalanie poczatkowych wartosci zmiennych
{
	srand((unsigned)time(NULL));
	platformy = new std::vector<platform*>; 
	serca = new std::vector<heart*>;
	monety = new std::vector<coin*>;
	bomby = new std::vector<bomb*>; 
	platformy->emplace_back(new platform(sf::Vector2f(200, 50), sf::Vector2f(2000, 900)));
	bomby->emplace_back(new bomb(sf::Vector2f(400, 20000)));
	game_speed = 0; 
	window = new sf::RenderWindow(sf::VideoMode(800, 1000), "Cloud tower",sf::Style::None); // tworzenie okna  
	minimap = new sf::RenderWindow(sf::VideoMode(500, 700), "MiniMap" , sf::Style::None);
	view_game = sf::View(sf::FloatRect(650, 790, 800.0f, 1000.0f));
	viev_minimap = sf::View(sf::FloatRect(1000, -2100, 2428, 3400));
	window->setFramerateLimit(60);
	minimap->setView(viev_minimap);
	minimap->setFramerateLimit(60); 
	minimap->setPosition(sf::Vector2i(50,300)); 
	map_number = 1; 
	background.draw_tlo(window);	
	serca->emplace_back(new heart(sf::Vector2f(0, 0) , sf::Vector2f(2,2))); 
	
}

void Game::generate_bombs(player player) // tworzenie i usuwanie bomb
{
	bomb_time = bomb_clock.getElapsedTime(); 
	if(bomby->size() == 0)
		bomby->emplace_back(new bomb(sf::Vector2f(player.getPosition().x - 500 + rand() % 1000, player.getPosition().y - 2500)));
	if (bomby->size() < 6 && bomb_time.asSeconds() > 2)
	{
		bomby->emplace_back(new bomb(sf::Vector2f(player.getPosition().x-500 + rand()%1000, player.getPosition().y - 2500)));
		bomb_clock.restart(); 
		std::cout << "tworze bombe " << std::endl;
	}
	if(bomby->front() != nullptr)
	if (bomby->front()->getPosition().y > player.getPosition().y + 500)
	{
		delete bomby->front(); 
		bomby->erase(bomby->begin()); 
	}
}

void Game::update_all(sf::RenderWindow *window , player& player) // aktualizuje wszystkie obiekty
{
	// update gracza na podstawie pozycji platform i innych rzeczy
	player.update(platformy, bomby, monety , serca);
	for (auto& x : *platformy) // updatowanie pozycji platform oraz rysowanie ich
	{
		x->update();
	}
	if (monety->size() > 0)
	for (auto& m : *monety)
	{
		m->update(); 
	}
	next_screen(player); // updatowanie pozycji bomb oraz platform 
    update_view(window, player);
	move_bombs();
	generate_platform(player); // sprawdzanie pozycji platform , nastepnie generowanie lub usuwanie zbednych platform
	generate_bombs(player); // to samo tylko z bombami 
	licznik_gracza.aktualizuj_wynik(player, view_game, window); // obiekt licznika gracza 
}

void Game::draw_all(sf::RenderWindow*window , player &player , bool if_coin_count , bool if_player) // rysowanie wszystkich obiektow
{
	background.draw_tlo(window); // rysowanie tla
	for (auto& x : *platformy)
	{
		window->draw(*x); 
	}
	for (auto& x : *bomby)
	{
		window->draw(*x);
	}	
	for (auto& m : *monety)
	{
		window->draw(*m);
	}
	for (auto& s : *serca)
	{
		window->draw(*s); 
	}
	if (if_player)
		window->draw(player);
	if(if_coin_count)
	licznik_gracza.draw(window); 

}

void Game::death(player& player, sf::RenderWindow*window) // ekran smierci 
{
	for (auto x : *bomby)
	{
		if (player.getGlobalBounds().intersects(x->getGlobalBounds()))
		{
			x->move(sf::Vector2f(-100, 0));
			bool blokada_animacji = true; 
			x->reset_clock();
			while (blokada_animacji)
			{
				window->clear(sf::Color::White);
				background.draw_tlo(window);
				draw_all(window , player , false , false);
				blokada_animacji = x->update();
				window->draw(*x);
				window->display();

			}
		}
	}
	system("CLS");
	std::cout << "Przegrales!" << std::endl;
	std::cout << "Wcisnij cokolwiek aby kontynuowac" << std::endl;
	std::cout << "Wynik gracza to: " <<player.return_score()<< std::endl;
	GameOver(player);
	//std::cin.get();
	//window->close();
}

void Game::pauza(sf::RenderWindow*window, player& gracz) // ekran pauzy 
{
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) // dodany element pauzy , gdy gracz jest w powietrzu 
	{
		MainMenu menu;
		// wywolujemy element klasy pauza ktory pobiera okno oraz rysuje swoje elementy na to
		// zaokraglamy pozycje elementow do liczb calkowtych aby elementy nie "skakaly" po ekranie 
		window->clear(); // nastepnie rysujemy nowa klatke , po czym przekazujemy tak narysowane okno do funkcji "Play"; 
		//background.draw_tlo(window);
		for (auto x : *platformy)
		{
			x->setPosition(std::round(x->getPosition().x), std::round(x->getPosition().y));
		}
		menu.PlayPauseMenu(window,gracz); 
		draw_all(window , gracz , true , true);
		window->draw(gracz);
		window->display();
		std::cout << "Zapauzowano!" << std::endl;
		//pause.Play(window);
		clock.restart();



	}
}

void Game::move_bombs() // rusza bomby
{
	for (auto& x : *bomby) // bomby 
	{
		x->move(sf::Vector2f(0, 2.5));
	}
}

void Game::ready_background_texture() // szykuje tekstury tla 
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

void Game::update_minimap(player player ) // aktualizuje minimape 
{
	minimap->clear(sf::Color::Blue);
	background.draw_tlo(minimap); 
	draw_all(minimap , player , false , true);
	minimap->draw(player); 
	//minimap->draw(*coin_count); 
	minimap->display(); 
}

void Game::zapis(player& play,std::string nick) // zapis do pliku 
{
	std::fstream zapis;
	zapis.open("Wyniki.csv", std::ios::app);
	zapis << play.return_score() << ',' << nick << std::endl;
	zapis.close();
}

void Game::GameOver(player& gracz) // ekran konca gry 
{
	sf::RenderWindow window2(sf::VideoMode(600, 400), "SFML works!", sf::Style::None);
	sf::Font font1,font2;
	std::string wynik = std::to_string(gracz.return_score());
	font1.loadFromFile("./assets/BigSmoke.ttf");
	font2.loadFromFile("./assets/FronzyFreeTrial-mLVlP.otf");
	sf::Texture background2;
	background2.loadFromFile("./assets/winter 1/1.png");
	sf::Sprite sprite;
	sprite.setTexture(background2);
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
	sf::Text text("", font2);
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
					platformy->clear();
					bomby->clear();
					monety->clear();
					gracz = player(1, sf::Vector2f(0, 0)); 
					background.ready_background_texture();
					ready_game();				
					play(); 
					
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

void Game::update_view(sf::RenderWindow* window , player player) // aktualizuje widok gry 
{
	view_game.setCenter(player.getPosition());
	window->setView(view_game);
	update_minimap(player);
}


