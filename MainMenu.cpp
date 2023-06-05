#include "MainMenu.h"


MainMenu::MainMenu()
{
	
}
MainMenu::~MainMenu()
{
	std::cout << "kasuje menu" << std::endl;
}

void MainMenu::MenuButtons(float width, float height)
{
	//wczytanie czcionki
	font.loadFromFile("./assets/BigSmoke.ttf");

	//ustawienie tytu³u
	title.setFont(font);
	title.setFillColor(sf::Color::Black);
	title.setCharacterSize(120);
	title.setString("Cloudy Tower");
	title.setPosition(sf::Vector2f(5, 50));
	//wprowadzenie tekstu na przycisków
	std::vector<sf::FloatRect> textbounds;
	std::vector<sf::FloatRect> buttonbounds;
	button.resize(3);
	buttontext.resize(3);
	buttontext[0].setString("GRAJ");
	buttontext[1].setString("OPCJE");
	buttontext[2].setString("WYJSCIE");
	//pêtla tworz¹ca przyciski
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

	sf::View view(window->getView());

	std::cout << "obiekt pauzy" << std::endl;
	font.loadFromFile("./assets/BigSmoke.ttf");

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

//przesuwanie opcji menu w górê
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

//przesuwanie opcji menu w dó³
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
	font.loadFromFile("./assets/BigSmoke.ttf");

	OptionButtons(static_cast<float>(optionwindow->getSize().x), (static_cast<float>( optionwindow->getSize().y)));

	bool option_window=true;
	while(option_window)
	{
		background.draw_menu_background(optionwindow);
		draw(optionwindow);
		optionwindow->draw(title);
		optionwindow->display();

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
									break;
								case 1:
									std::cout<<"autorzy" <<std::endl;
									break;
								case 2:
									std::cout << "powrot do menu!" <<std::endl;
									option_window=!option_window;
									optionwindow->close();
									delete optionwindow;
									break;
							}
							break;
					}

					break;
				case sf::Event::Closed:
					optionwindow->close();

					break;

			}
		}

	
	}

}

enum MainMenu::buttons
{
	_GRAJ,
	_OPCJE,
	_WYJSCIE

};



void MainMenu::PlayMainMenu(sf::RenderWindow *window)
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
void MainMenu::PlayPauseMenu(sf::RenderWindow* window, player &play)
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