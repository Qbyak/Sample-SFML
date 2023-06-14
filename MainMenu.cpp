#include "MainMenu.h"


MainMenu::MainMenu()
{
	std::cout << "tworze menu" << std::endl;
}
MainMenu::~MainMenu()
{
	std::cout << "kasuje menu" << std::endl;
}
void MainMenu::LoadFonts()
{
	font.loadFromFile("./assets/BigSmoke.ttf");
	text_font.loadFromFile("./assets/FronzyFreeTrial-mLVlP.otf");
}
void MainMenu::MenuButtons(float width, float height)
{
	LoadFonts();
	//ustawienie tytu�u
	title.setFont(font);
	title.setFillColor(sf::Color::Black);
	title.setCharacterSize(120);
	title.setString("Cloudy Tower");
	title.setPosition(sf::Vector2f(5, 50));
	//wprowadzenie tekstu na przycisk�w
	std::vector<sf::FloatRect> textbounds;
	std::vector<sf::FloatRect> buttonbounds;
	button.resize(3);
	buttontext.resize(3);
	buttontext[0].setString("GRAJ");
	buttontext[1].setString("OPCJE");
	buttontext[2].setString("WYJSCIE");
	//p�tla tworz�ca przyciski
	for(int i = 0; i < MAX_NUMBER_OF_BUTTONS; i++)
	{
		//ustawienie tekstu na przyciskach
		buttontext[i].setFont(font);
		buttontext[i].setFillColor(sf::Color::Black);
		buttontext[i].setCharacterSize(70);
		buttontext[i].setPosition(sf::Vector2f(400, (250 * (i + 1)) + 20));
		textbounds.emplace_back(buttontext[i].getLocalBounds());
		buttontext[i].setOrigin(sf::Vector2f(textbounds[i].left + textbounds[i].width / 2, textbounds[i].top + textbounds[i].height / 2));

		button[i].setSize(sf::Vector2f(textbounds[i].width + 5.0, 80));
		buttonbounds.emplace_back(button[i].getLocalBounds());

		//ustawienie reszty przycisku
		button[i].setFillColor(sf::Color(255, 247, 226));
		button[i].setOutlineColor(sf::Color::Black);
		button[i].setOutlineThickness(5);
		button[i].setOrigin(sf::Vector2f(buttonbounds[i].left + buttonbounds[i].width / 2, buttonbounds[i].top + buttonbounds[i].height / 2));
		button[i].setPosition(sf::Vector2f(400, (250 * (i + 1)) + 20));
	}

	selectedItemIndex = 1;

}
void MainMenu::PauseButtons(sf::RenderWindow* window)
{
	LoadFonts();
	sf::View view(window->getView());
	std::cout << "obiekt pauzy" << std::endl;

	title.setFont(font);
	title.setFillColor(sf::Color::Black);

	title.setCharacterSize(100);
	title.setString("PAUZA");
	title.setPosition(sf::Vector2f(view.getCenter().x + 250, view.getCenter().y + 50));

	

	//TEKST PRZYCISKU GRAJ
	button.resize(2);
	buttontext.resize(2);
	buttontext[0].setString("WZNOW");
	buttontext[1].setString("WYJSCIE");
	for(int i = 0; i < 2; i++)
	{
		buttontext[i].setFont(font);
		buttontext[i].setFillColor(sf::Color::Black);
		buttontext[i].setCharacterSize(70);
		buttontext[i].setPosition(sf::Vector2f(view.getCenter().x + 400, view.getCenter().y + (320 * (i + 1)) + 50));
		textbounds.emplace_back(buttontext[i].getLocalBounds());
		buttontext[i].setOrigin(sf::Vector2f(textbounds[i].left + textbounds[i].width / 2, textbounds[i].top + textbounds[i].height / 2));

		button[i].setSize(sf::Vector2f(textbounds[i].width + 5.0, 80));
		buttonbounds.emplace_back(button[i].getLocalBounds());

		button[i].setFillColor(sf::Color(255, 247, 226));
		button[i].setOutlineColor(sf::Color::Black);
		button[i].setOutlineThickness(5);
		button[i].setOrigin(sf::Vector2f(buttonbounds[i].left + buttonbounds[i].width / 2, buttonbounds[i].top + buttonbounds[i].height / 2));
		button[i].setPosition(sf::Vector2f(view.getCenter().x + 400, view.getCenter().y + (320 * (i + 1)) + 50));
	}
	pauseBackground.setFillColor(sf::Color(0, 0, 0, 1));
	pauseBackground.setSize(sf::Vector2f(800, 1000));
	pauseBackground.setPosition(sf::Vector2f(view.getCenter().x, view.getCenter().y));
	selectedItemIndex = 0;

}
void MainMenu::OptionButtons(float width, float height)
{
	title.setFont(font);
	title.setFillColor(sf::Color::Black);
	title.setCharacterSize(100);
	title.setString("OPCJE");
	title.setPosition(250, 50);
	button.clear();
	buttontext.clear();
	button.resize(3);
	buttontext.resize(3);
	buttontext[0].setString("TABLICA WYNIKOW");
	buttontext[1].setString("AUTORZY");
	buttontext[2].setString("POWROT");
	for(int i = 0; i < 3; i++)
	{
		//ustawienie tekstu na przyciskach
		buttontext[i].setFont(font);
		buttontext[i].setFillColor(sf::Color::Black);
		buttontext[i].setCharacterSize(40);
		buttontext[i].setPosition(sf::Vector2f(400, (250 * (i + 1)) + 20));
		textbounds.emplace_back(buttontext[i].getLocalBounds());
		buttontext[i].setOrigin(sf::Vector2f(textbounds[i].left + textbounds[i].width / 2, textbounds[i].top + textbounds[i].height / 2));

		button[i].setSize(sf::Vector2f(textbounds[i].width + 5.0, 80));
		buttonbounds.emplace_back(button[i].getLocalBounds());

		//ustawienie reszty przycisku
		button[i].setFillColor(sf::Color(255, 247, 226));
		button[i].setOutlineColor(sf::Color::Black);
		button[i].setOutlineThickness(5);
		button[i].setOrigin(sf::Vector2f(buttonbounds[i].left + buttonbounds[i].width / 2, buttonbounds[i].top + buttonbounds[i].height / 2));
		button[i].setPosition(sf::Vector2f(400, (250 * (i + 1)) + 20));
	}
}
int MainMenu::GetPressedItem()
{
	return selectedItemIndex;
}

void MainMenu::draw(sf::RenderWindow* window)
{  
	window->draw(title);
	for(int i = 0; i < std::size(button); i++)
	{
		window->draw(button[i]);
		window->draw(buttontext[i]);
	}
}

//przesuwanie opcji menu w g�r�
void MainMenu::MoveUp()
{
	if(selectedItemIndex - 1 >= 0)
	{
		buttontext[selectedItemIndex].setFillColor(sf::Color::Black);
		button[selectedItemIndex].setOutlineColor(sf::Color::Black);
		selectedItemIndex--;
		buttontext[selectedItemIndex].setFillColor(sf::Color::Red);
		button[selectedItemIndex].setOutlineColor(sf::Color::Red);
	}
}

//przesuwanie opcji menu w d�
void MainMenu::MoveDown()
{
	if(selectedItemIndex + 1 < std::size(button))
	{
		buttontext[selectedItemIndex].setFillColor(sf::Color::Black);
		button[selectedItemIndex].setOutlineColor(sf::Color::Black);
		selectedItemIndex++;
		buttontext[selectedItemIndex].setFillColor(sf::Color::Red);
		button[selectedItemIndex].setOutlineColor(sf::Color::Red);
	}
}

void MainMenu::PlayOptions()
{
	sf::RenderWindow* optionwindow;
	optionwindow= new sf::RenderWindow(sf::VideoMode(800,1000),"Opcje",sf::Style::None);

	OptionButtons(static_cast<float>(optionwindow->getSize().x), (static_cast<float>( optionwindow->getSize().y)));

	bool option_window=true;
	while(option_window)
	{
		sf::Event event;
		while(optionwindow->pollEvent(event))
		{
			switch(event.type)
			{
				case sf::Event::KeyReleased:
					switch(event.key.code)
					{
						case sf::Keyboard::Up:
							std::cout << "opcja wyzej" << std::endl;
							MoveUp();
							break;

						case sf::Keyboard::Down:
							std::cout << "opcja nizej" << std::endl;
							MoveDown();
							break;

						case sf::Keyboard::Return:
							switch(GetPressedItem())
							{
								case 0:
									std::cout << "Tablica Wynikow!" << std::endl;
									odczyt();
									break;
								case 1:
									std::cout<<"autorzy" <<std::endl;
									autorzy();
									break;
								case 2:
									std::cout << "powrot do menu!" <<std::endl;
									option_window=!option_window;
									optionwindow->close();

									break;
							}
							break;
					}

					break;
				case sf::Event::Closed:
					optionwindow->close();
					break;

			}
		background.draw_menu_background(optionwindow);
		draw(optionwindow);
		optionwindow->draw(title);
		optionwindow->display();
		}
		

	
	}
	delete optionwindow;
}



enum MainMenu::buttons
{
	_GRAJ,
	_OPCJE,
	_WYJSCIE

};



void MainMenu::PlayMainMenu(sf::RenderWindow *window, sf::RenderWindow* minimap)
{
	MainMenu::buttons button = MainMenu::buttons::_OPCJE;

	background.ready_background_texture();
	MenuButtons(800.0,1000.0);

	bool petla=true;
	while(petla)
	{
		sf::Event event;
		
		while(window->pollEvent(event))
		{
			switch(event.type)
			{
				case sf::Event::KeyReleased:
					switch(event.key.code)
					{
						case sf::Keyboard::Up:
							{
							if(button==_OPCJE)
								button=_GRAJ;
							else if(button==_WYJSCIE)
								button=_OPCJE;
							MoveUp();
							break;
							}
						case sf::Keyboard::Down:
							{
							if(button == _OPCJE)
								button=_WYJSCIE;
							else if(button == _GRAJ)
								button = _OPCJE;
							MoveDown();
							break;
							}
						case sf::Keyboard::Return:
							switch(button)
							{
								case _GRAJ:
									petla=false;
									std::cout << "opcja GRAJ" << std::endl;
									break;
								case _OPCJE:
									PlayOptions();
									MenuButtons(800.0, 1000.0);
									std::cout << "opcja OPCJE" << std::endl;
									break;
								case _WYJSCIE:
									std::cout<<"papa" << std::endl;
									window->close();
									minimap->close();
									break;
							}

							break;
					}
			}
			background.draw_menu_background(window);
			draw(window);
			window->display();
		}
  }
  
}
void MainMenu::PlayPauseMenu(sf::RenderWindow* window, sf::RenderWindow* minimap, player &play)
{
	background.ready_background_texture();
	bool pauza = true;
	PauseButtons(window);

	while(pauza)
	{
		sf::Event event;
		while(window->pollEvent(event))
		{
			switch(event.type)
			{
				case sf::Event::KeyReleased:
					switch(event.key.code)
					{
						case sf::Keyboard::Up:
							std::cout << "opcja wyzej" << std::endl;
							MoveUp();
							break;

						case sf::Keyboard::Down:
							std::cout << "opcja nizej" << std::endl;
							MoveDown();
							break;

						case sf::Keyboard::Return:
							switch(GetPressedItem())
							{
								case 0:
									pauza = !pauza;
									std::cout << "Wznowiono gre!" << std::endl;
									break;
								case 1:
									window->close();
									minimap->close();
									break;
							}
							break;
					}

					break;
				case sf::Event::Closed:
					window->close();

					break;

			}
		}

		background.draw_pause_background(window,play);
		draw(window);
		
		window->display();
	}
}

void MainMenu::odczyt() //odczyt wynik�w graczy z pliku csv oraz ich sortowanie i wy�wietlenie
{
	std::fstream file("Wyniki.csv", std::fstream::in);

	if (file.is_open())
	{
		std::string line;

		while (getline(file, line))
		{
			std::stringstream str(line);
			do_zapisu er;
			std::string scor_in;
			getline(str, scor_in, ',');
			er.score = stoi(scor_in);
			getline(str, er.name, ',');
			posortowany.emplace_back(er);

		}
	}

	std::sort(posortowany.begin(), posortowany.end(), [](const do_zapisu& A, const do_zapisu& B) {return A.score < B.score; });
	std::reverse(posortowany.begin(), posortowany.end());

	for (int i = 0; i < posortowany.size(); i++)
	{
		std::cout << posortowany[i];
	}



	sf::RenderWindow* score_window;
	score_window = new sf::RenderWindow(sf::VideoMode(800, 1000), "Tablica wynikow", sf::Style::None);

	sf::Text text1, tytul, text3, exit;
	std::string lp_nick, wynik;

	tytul.setString("Tablica Wynikow");
	tytul.setCharacterSize(70);
	tytul.setFillColor(sf::Color::Black);
	tytul.setPosition(125, 50);
	tytul.setFont(font);

	
	for (int i = 0; i<posortowany.size()&&i<20; i++)
	{
		lp_nick = std::to_string(i + 1) + ". " + posortowany[i].name;
		wynik = std::to_string(posortowany[i].score);
		text1.setString(lp_nick);
		text3.setString(wynik);
		text1.setCharacterSize(35);
		text3.setCharacterSize(35);
		text1.setFillColor(sf::Color::Black);
		text3.setFillColor(sf::Color::Black);
		text1.setPosition(250, 150 + (35 * i));
		text3.setPosition(500, 150 + (35 * i));
		text1.setFont(text_font);
		text3.setFont(text_font);
		tab.emplace_back(text1);
		tab.emplace_back(text3);
		lp_nick.clear();
		wynik.clear();
	}
	exit.setString("Nacisnij esc zeby wrocic");
	exit.setCharacterSize(40);
	exit.setFillColor(sf::Color::Black);
	exit.setPosition(400, 900);
	exit.setFont(text_font);

	score_window->clear();

	while (score_window->isOpen())
	{
		sf::Event event;
		while (score_window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				score_window->close();
			else if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					score_window->close();
					score_window->clear();
					tab.clear();
					posortowany.clear();
					system("cls");
				}
			}
		}
		score_window->clear();
		background.draw_menu_background(score_window);
		score_window->draw(tytul);
		if(posortowany.size()>0)
		{ 
		for (int i = 0; i < tab.size(); i++)
		{
			score_window->draw(tab[i]);
		}
		}
		score_window->draw(exit);
		score_window->display();
	}
	delete score_window;
}

void MainMenu::autorzy() // okno wy�wietlaj�ce autor�w
{
	
	sf::RenderWindow* window4;
	window4 = new sf::RenderWindow(sf::VideoMode(800, 1000), "Autorzy!", sf::Style::None);

	LoadFonts();
	sf::Text text[5];
	std::vector<sf::FloatRect> textbounds;
	text[0].setString("TWORCY GRY");
	text[1].setString("Wiktor Krakowski");
	text[2].setString("Hubert Kubiak");
	text[3].setString("Jakub Kubiak");
	for(int i = 0; i < 4; i++)
	{
		text[i].setFont(font);
		text[i].setCharacterSize(70);
		text[i].setFillColor(sf::Color::Black);
		textbounds.emplace_back(text[i].getLocalBounds());
		text[i].setOrigin(sf::Vector2f(textbounds[i].left+textbounds[i].width/2.0f, textbounds[i].top + textbounds[i].height / 2.0f));
		text[i].setPosition(sf::Vector2f(400.0f,100.0f*(i+10)));
	}
	text[0].setPosition(sf::Vector2f(400.0f, 100.0f ));
	text[4].setString("Nacisnij esc zeby wrocic");
	text[4].setCharacterSize(40);
	text[4].setFillColor(sf::Color::Black);
	text[4].setPosition(400, 900);
	text[4].setFont(text_font);

	sf::Clock clock;

	while (window4->isOpen())
	{
		clock.restart().asSeconds();
		ruch.y -= 10 * clock.getElapsedTime().asSeconds();
		sf::Event event4;
		while (window4->pollEvent(event4))
		{
			if (event4.type == sf::Event::Closed)
				window4->close();
			else if (event4.type == sf::Event::KeyReleased)
			{
				if (event4.key.code == sf::Keyboard::Escape)
				{
					window4->close();
					window4->clear();
					clock.restart();
					ruch.y = 0;
				}
			}
		}
		if (ruch.y >= 0.5)
		{
			ruch.y = 0.5;
		}
		window4->clear();
		background.draw_menu_background(window4);
		
		if (text[1].getPosition().y > 300)
		{
			for (int i = 1; i < 4; i++)
			{
				text[i].move(ruch);
			}
		}
		if (text[1].getPosition().y < 401)
		{
			window4->draw(text[4]);
		}

		for (int i = 0; i < 4; i++)
		{
			window4->draw(text[i]);
		}
		window4->display();
	}
	delete window4;
}
void MainMenu::zapis(player& play, std::string nick) // zapis do pliku 
{
	std::fstream zapis;
	zapis.open("Wyniki.csv", std::ios::app);
	zapis << play.return_score() << ',' << nick << std::endl;
	zapis.close();
}

void MainMenu::GameOver(player& gracz,sf::RenderWindow*window, std::vector<platform*>* platformy,std::vector<bomb*>* bomby,std::vector<coin*>* monety,
	sf::RenderWindow* minimap) // ekran konca gry 
{
	sf::RenderWindow window2(sf::VideoMode(600, 400), "SFML works!", sf::Style::None);
	LoadFonts();
	std::string wynik = std::to_string(gracz.return_score());

	sf::Texture background2;
	background2.loadFromFile("./assets/winter 8/1.png");
	sf::Sprite sprite;
	sprite.setTexture(background2);
	sprite.setScale(3, 3);

	sf::Text t[5];
	t[0].setString("Game over");
	t[0].setCharacterSize(50);
	t[0].setFillColor(sf::Color::Black);
	t[0].setPosition(170, 30);
	t[0].setFont(font);

	t[1].setString("Twoj wynik");
	t[1].setCharacterSize(30);
	t[1].setFillColor(sf::Color::Black);
	t[1].setPosition(150, 125);
	t[1].setFont(font);

	t[2].setString(wynik);
	t[2].setCharacterSize(30);
	t[2].setFillColor(sf::Color::Black);
	t[2].setPosition(450, 125);
	t[2].setFont(font);

	t[3].setString("Podaj swoj nick i nacisnij enter aby wrocic do menu");
	t[3].setCharacterSize(22);
	t[3].setFillColor(sf::Color::Black);
	t[3].setPosition(50, 200);
	t[3].setFont(font);

	t[4].setString("NICK: ");
	t[4].setCharacterSize(40);
	t[4].setFillColor(sf::Color::Black);
	t[4].setPosition(150, 300);
	t[4].setFont(text_font);



	std::string input_text;
	sf::Text text("", text_font);
	sf::Clock clock;




	while(window2.isOpen())
	{
		sf::Event event2;
		while(window2.pollEvent(event2))
		{
			if(event2.type == sf::Event::Closed)
				window2.close();
			else if(event2.type == sf::Event::TextEntered)
			{
				if(std::isprint(event2.text.unicode) && input_text.size() < 10)
					input_text += event2.text.unicode;
			}
			else if(event2.type == sf::Event::KeyReleased)
			{
				if(event2.key.code == sf::Keyboard::BackSpace)
				{
					if(!input_text.empty())
						input_text.pop_back();
				}
				if(event2.key.code == sf::Keyboard::Enter && !input_text.empty())
				{
					window2.close();

					zapis(gracz, input_text);
					window->close();
					minimap->close();
					platformy->clear();
					bomby->clear();
					monety->clear();
					gracz = player();
					background.ready_background_texture();
				}
			}
		}

		static sf::Time text_effect_time;
		static bool show_cursor;

		text_effect_time += clock.restart();

		if(text_effect_time >= sf::seconds(0.5f))
		{
			show_cursor = !show_cursor;
			text_effect_time = sf::Time::Zero;
		}

		text.setString(input_text + (show_cursor ? '_' : ' '));
		text.setPosition(350, 300);
		text.setFillColor(sf::Color::Black);


		window2.clear();
		window2.draw(sprite);
		for(int i = 0; i < 5; i++)
		{
			window2.draw(t[i]);
		}
		window2.draw(text);
		window2.display();
	}
}