#include "Game.h"
Game::Game()
{
	background.ready_background_texture();
	ready_game();
}

void Game::play()
{
	menu.PlayMainMenu(window,minimap); // wyswietla menu gry 
	while(window->isOpen()) // Glowna petla gry 
	{
		window->clear(sf::Color::Black); // czyszczenie ekranu 
		close_window(window); // zamykanie okna 
		update_all(window , gracz); // updatowanie wszystkich obiektow
        draw_all(window , gracz , true , true); // rysowanie wszystkich obiektow
		if (gracz.get_status() == player::dead) // sprawdzanie warunku konca gry  , sam status dead czy alive jest aktualizowany w funkcji update gracza
		{
			death(gracz, window); //jezeli gracz jest 'dead' to funkcja konczy gre 
		}
		pauza(window, gracz);
		window->display();// wyswietlanie klatki gry		
	}
	clear_all(window,minimap,platformy,bomby,monety,serca);
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
			if (x->getPosition().y  > player.getPosition().y + 600 ) 
			{
				auto element = std::find(platformy->begin(), platformy->end(), x);

					delete x;
					platformy->erase(element);
			}
		}
		if(monety->size()>0)
			for (auto m : *monety)
			{
				if (m->getPosition().y > player.getPosition().y + 400)
				{
					auto element = std::find(monety->begin(), monety->end(), m);
					if (element != monety->end())
					{
						delete m;
						monety->erase(element);
					}
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
		bomby->clear();
		monety->clear();
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
		bomby->clear();
		monety->clear();
		serca->clear(); 
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
		serca->clear();
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
	gracz.setPosition(sf::Vector2f(2100, 800)); 
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
	if (bomby->size() < 10 && bomb_time.asSeconds() > 2.5)
	{
		bomby->emplace_back(new bomb(sf::Vector2f(player.getPosition().x-500 + rand()%1000, player.getPosition().y - 2500)));
		bomb_clock.restart(); 
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
	player.update(platformy, bomby, monety , serca , event);
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
		if(window->isOpen())
		{ 
		menu.GameOver(player, window,platformy,bomby,monety, minimap);
		ready_game();
		play();
		}
	}
}

void Game::pauza(sf::RenderWindow*window, player& gracz) // ekran pauzy 
{
	if(window->isOpen())
	{ 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) // dodany element pauzy , gdy gracz jest w powietrzu 
	{
	
		menu.PlayPauseMenu(window,minimap,gracz); 
		window->display();
		clock.restart();
	}
	}
}

void Game::move_bombs() // rusza bomby
{
	for (auto& x : *bomby) // bomby 
	{
		x->move(sf::Vector2f(0, 2.5));
	}
}

void Game::clear_all(sf::RenderWindow* window, sf::RenderWindow* minimap, std::vector<platform*>* platformy,
	std::vector<bomb*>* bomby, std::vector<coin*>* monety, std::vector<heart*>* serca)
{
	platformy->clear();
	bomby->clear();
	monety->clear();
	serca->clear();
	std::cout << "czyszczenie pamieci" << std::endl;
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