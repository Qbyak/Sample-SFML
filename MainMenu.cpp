#include "MainMenu.h"



MainMenu::MainMenu()//konstruktor menu, wczytywanie tekstur t³a
{
	std::cout << "tworze menu" << std::endl;
	background.ready_background_texture();
	selectedButtonIndex = 0; 
}
MainMenu::~MainMenu()
{
	std::cout << "kasuje menu" << std::endl;
}
void MainMenu::LoadFonts()//wczytywanie czcionek
{
	font.loadFromFile("./assets/BigSmoke.ttf");//czcionka tytulowa i przyciskow
	text_font.loadFromFile("./assets/FronzyFreeTrial-mLVlP.otf");//czcionka tabeli wynikow
}
void MainMenu::MenuButtons()//przyciski menu g³ównego
{
	LoadFonts();
	//ustawienie tytu³u
	title.setFont(font);
	title.setFillColor(sf::Color::Black);
	title.setCharacterSize(120);
	title.setString("Cloudy Tower");
	title.setPosition(sf::Vector2f(5, 50));
	//ustawienie ilosci przyciskow w danym menu
	button.resize(3);
	buttontext.resize(3);
	//wprowadzenie tekstu na przycisków
	buttontext[0].setString("GRAJ");
	buttontext[1].setString("OPCJE");
	buttontext[2].setString("WYJSCIE");
	//pêtla tworz¹ca przyciski
	for(int i = 0; i < button.size(); i++)
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

	selectedButtonIndex = 1;
	//czyszczenie wektorow
	textbounds.clear();
	buttonbounds.clear();
}
void MainMenu::PauseButtons(sf::RenderWindow* window) //przyciski menu pauzy
{
	LoadFonts();
	sf::View view(window->getView());//uzyskanie widoku okna
	std::cout << "obiekt pauzy" << std::endl;
	//ustawienie napisu PAUZA
	title.setFont(font);
	title.setFillColor(sf::Color::Black);
	title.setCharacterSize(100);
	title.setString("PAUZA");
	title.setPosition(sf::Vector2f(view.getCenter().x + 250, view.getCenter().y + 50));//ustawienie pozycji przycisków pod widok

	

	//analogicznie do pêtli menu
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
	selectedButtonIndex = 1;
	textbounds.clear();
	buttonbounds.clear();
}
void MainMenu::OptionButtons()//przyciski menu opcji
{
	//analogicznie do poprzednich menu
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
	textbounds.clear();
	buttonbounds.clear();
}
int MainMenu::GetPressedItem()
{
	return selectedButtonIndex;
}

void MainMenu::draw(sf::RenderWindow* window)//rysowanie przyciskow i tytulu danego menu na ekran
{  
	window->draw(title);
	for(int i = 0; i < std::size(button); i++)
	{
		window->draw(button[i]);
		window->draw(buttontext[i]);
	}
}

//przesuwanie opcji menu w górê
void MainMenu::MoveUp()
{
	if(selectedButtonIndex - 1 >= 0)
	{
		buttontext[selectedButtonIndex].setFillColor(sf::Color::Black);
		button[selectedButtonIndex].setOutlineColor(sf::Color::Black);
		selectedButtonIndex--;
		buttontext[selectedButtonIndex].setFillColor(sf::Color::Red);
		button[selectedButtonIndex].setOutlineColor(sf::Color::Red);
	}
}

//przesuwanie opcji menu w dó³
void MainMenu::MoveDown()
{
	if(selectedButtonIndex + 1 < std::size(button))
	{
		buttontext[selectedButtonIndex].setFillColor(sf::Color::Black);
		button[selectedButtonIndex].setOutlineColor(sf::Color::Black);
		selectedButtonIndex++;
		buttontext[selectedButtonIndex].setFillColor(sf::Color::Red);
		button[selectedButtonIndex].setOutlineColor(sf::Color::Red);
	}
}

void MainMenu::PlayOptions()//pêtla menu opcji
{
	//tworzenie okna opcji
	sf::RenderWindow* optionwindow;
	optionwindow= new sf::RenderWindow(sf::VideoMode(800,1000),"Opcje",sf::Style::None);
	//wprowadzenie danych okna do metody z przyciskami
	OptionButtons();
	MoveUp();
	MoveDown();
	bool option_window=true;//inicjalizacja pêtli opcji
	while(option_window)
	{
		sf::Event event;
		while(optionwindow->pollEvent(event))
		{
			switch(event.type)
			{
				//prze³¹czanie pomiêdzy przyciskami
				case sf::Event::KeyReleased:
					switch(event.key.code)
					{
						case sf::Keyboard::Up:
							
							MoveUp();
							break;

						case sf::Keyboard::Down:
							
							MoveDown();
							break;
							//nacisniecie przycisku
						case sf::Keyboard::Return:
							switch(GetPressedItem())
							{
								case 0:
									
									odczyt();//odczyt tabeli wynikow z pliku i przedstawienie jej
									break;
								case 1:
									
									autorzy();//przedstawienie autorow w nowym oknie
									break;
								case 2:
									
									option_window=!option_window;//zakonczenie pêtli menu opcji, powrót do menu
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

void MainMenu::PlayMainMenu(sf::RenderWindow *window, sf::RenderWindow* minimap)//pêtla menu g³ownego
{
	
	MenuButtons();
	MoveUp();
	MoveDown();
	_button = _OPCJE;
	bool petla=true;//petla menu
	while(petla)
	{
		sf::Event event;
		
		while(window->pollEvent(event))
		{
			switch(event.type)
			{//wybór przycisku 
				case sf::Event::KeyReleased:
					switch(event.key.code)
					{
						case sf::Keyboard::Up:
							{
							if(_button==_OPCJE)
								_button=_GRAJ;
							else if(_button==_WYJSCIE)
								_button=_OPCJE;
							MoveUp();
							break;
							}
						case sf::Keyboard::Down:
							{
							if(_button == _OPCJE)
								_button=_WYJSCIE;
							else if(_button == _GRAJ)
								_button = _OPCJE;
							MoveDown();
							break;
							}
						case sf::Keyboard::Return:
							switch(_button)
							{
								case _GRAJ:
									petla=false;//zakonczenie petli, przejscie do gry
									
									break;
								case _OPCJE:
									PlayOptions();//uruchomienie menu opcji
									MenuButtons(); //powrot do przyciskow menu glownego
									MoveUp();
									MoveDown();
									break;
								case _WYJSCIE://wyjscie z gry
									petla=false;
									
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
void MainMenu::PlayPauseMenu(sf::RenderWindow* window, sf::RenderWindow* minimap, player &play)//pêtla menu pauzy
{
	
	bool pauza = true;//petla pauzy
	PauseButtons(window);//inicjalizacja przyciskow
	MoveUp();//ustawienie domyœlne przycisku na WZNÓW
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
							
							MoveUp();
							break;

						case sf::Keyboard::Down:
							
							MoveDown();
							break;

						case sf::Keyboard::Return:
							switch(GetPressedItem())
							{
								case 0:
									pauza = !pauza;//powrot do gry
									
									break;
								case 1:
									pauza=!pauza;
									_button=_WYJSCIE;
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

void MainMenu::odczyt() //odczyt wyników graczy z pliku csv oraz ich sortowanie i wyœwietlenie
{
	std::fstream file("Wyniki.csv", std::fstream::in);//otworzenie i utworzenie pliku
	//stworzenie okna pod tablicê wynikow
	sf::RenderWindow* score_window;
	score_window = new sf::RenderWindow(sf::VideoMode(800, 1000), "Tablica wynikow", sf::Style::None);

	sf::Text NickLp, tytul, score, exit;
	std::string lp_nick, wynik;

	if (file.is_open())
	{
		std::string line;
		//oddzielanie wyniku od nicku
		while (getline(file, line))
		{
			std::stringstream str(line);
			do_zapisu wynik_nick;
			std::string scor_in;
			getline(str, scor_in, ',');
			wynik_nick.score = stoi(scor_in);
			getline(str, wynik_nick.name, ',');
			posortowany.emplace_back(wynik_nick);

		}
	}
	//sortowanie wynikow za pomoc¹ lambdy rosn¹co
	std::sort(posortowany.begin(), posortowany.end(), [](const do_zapisu& A, const do_zapisu& B) {return A.score < B.score; });
	//odwrócenie wektora aby wyniki by³y posortowane malej¹co
	std::reverse(posortowany.begin(), posortowany.end());
	//odczyt wszystkich wyników w konsoli
	for (int i = 0; i < posortowany.size(); i++)
	{
		std::cout << posortowany[i];
	}

	tytul.setString("Tablica Wynikow");
	tytul.setCharacterSize(70);
	tytul.setFillColor(sf::Color::Black);
	tytul.setPosition(125, 50);
	tytul.setFont(font);

	//ustawienie parametrów pierwszych 20 wyników do pokazania na ekranie
	for (int i = 0; i<posortowany.size()&&i<20; i++)
	{
		lp_nick = std::to_string(i + 1) + ". " + posortowany[i].name;
		wynik = std::to_string(posortowany[i].score);
		NickLp.setString(lp_nick);
		score.setString(wynik);
		NickLp.setCharacterSize(35);
		score.setCharacterSize(35);
		NickLp.setFillColor(sf::Color::Black);
		score.setFillColor(sf::Color::Black);
		NickLp.setPosition(250, 150 + (35 * i));
		score.setPosition(500, 150 + (35 * i));
		NickLp.setFont(text_font);
		score.setFont(text_font);
		tab.emplace_back(NickLp);
		tab.emplace_back(score);
		lp_nick.clear();
		wynik.clear();
	}
	
	exit.setString("Nacisnij esc zeby wrocic");
	exit.setCharacterSize(40);
	exit.setFillColor(sf::Color::Black);
	exit.setPosition(400, 900);
	exit.setFont(text_font);

	score_window->clear();
	//wyswietlanie tabeli wynikow na ekranie
	while (score_window->isOpen())
	{
		sf::Event event;
		while (score_window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				score_window->close();
			else if (event.type == sf::Event::KeyReleased)
			{ 
				//zamykanie okna po wciœniêciu escape
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

void MainMenu::autorzy() // okno wyœwietlaj¹ce autorów
{
	
	sf::RenderWindow* window4;
	window4 = new sf::RenderWindow(sf::VideoMode(800, 1000), "Autorzy!", sf::Style::None);
	sf::Vector2f ruch;
	//tworzenie napisów
	LoadFonts();
	sf::Text text[5];
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
		//animacja napisów
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
	textbounds.clear();
	delete window4;
}
void MainMenu::zapis(player& play, std::string nick) // zapis do pliku 
{
	std::fstream zapis;
	zapis.open("Wyniki.csv", std::ios::app);
	zapis << play.return_score() << ',' << nick << std::endl;
	zapis.close();
}

void MainMenu::GameOver(player& player,sf::RenderWindow*window, std::vector<platform*>* platformy,std::vector<bomb*>* bomby,std::vector<coin*>* monety,
	sf::RenderWindow* minimap) // ekran konca gry 
{
	sf::RenderWindow window2(sf::VideoMode(600, 400), "SFML works!", sf::Style::None);
	LoadFonts();
	std::string wynik = std::to_string(player.return_score());

	sf::Texture background2;
	background2.loadFromFile("./assets/winter 8/1.png");
	sf::Sprite sprite;
	sprite.setTexture(background2);
	sprite.setScale(3, 3);
	//tworzenie napisow w oknie
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



	//resetowanie gry, wprowadzanie nicku i zamykanie okna
	while(window2.isOpen())
	{
		sf::Event event2;
		while(window2.pollEvent(event2))
		{
			if(event2.type == sf::Event::Closed)
				window2.close();
			else if(event2.type == sf::Event::TextEntered)
			{
				//zamiana unicode na char
				if(std::isprint(event2.text.unicode) && input_text.size() < 10)//ograniczenie do 10 znaków
					input_text += event2.text.unicode;
			}
			else if(event2.type == sf::Event::KeyReleased)
			{
				//umo¿liwienie kasowania znaków przy pomy³ce
				if(event2.key.code == sf::Keyboard::BackSpace)
				{
					if(!input_text.empty())
						input_text.pop_back();
				}
				//zamykanie gry
				if(event2.key.code == sf::Keyboard::Enter && !input_text.empty())//zabezpieczenie przed pustym nickiem
				{
					window2.close();
					
					zapis(player, input_text);
					window->close();
					minimap->close();
					platformy->clear();
					bomby->clear();
					monety->clear();
					player.setParameters();
					//std::cout << "czyszczenie pamieci po przegranej" <<std::endl;
				}
			}
		}
		//tworzenie migaj¹cego kursora
		static sf::Time text_effect_time;
		static bool show_cursor;

		text_effect_time += clock.restart();

		if(text_effect_time >= sf::seconds(0.5f)&& input_text.size() < 10)
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