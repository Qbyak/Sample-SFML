#include "MainMenu.h"
#include "Game.h"

MainMenu::MainMenu(float width, float height)
{
	
}
void MainMenu::MenuButtons(float width, float height)
{
	//wczytanie czcionki
	font.loadFromFile("./assets/BigSmoke.ttf");

	//ustawienie tytu�u
	title.setFont(font);
	title.setFillColor(sf::Color::Black);
	title.setCharacterSize(120);
	title.setString("Cloudy Tower");
	title.setPosition(sf::Vector2f(5, 50));
	//wektory zawieraj�ce granice tektu i t�a przycisku
	std::vector<sf::FloatRect> textbounds;
	std::vector<sf::FloatRect> buttonbounds;

	//wprowadzenie tekstu na przycisk�w
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
MainMenu::~MainMenu()
{
	std::cout << "kasuje menu" << std::endl;
}

int MainMenu::GetPressedItem()
{
	return selectedItemIndex;
}

void MainMenu::draw(sf::RenderWindow* window)
{  
	window->draw(title);
	for(int i = 0; i < MAX_NUMBER_OF_BUTTONS; i++)
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
	if(selectedItemIndex + 1 < MAX_NUMBER_OF_BUTTONS)
	{
		buttontext[selectedItemIndex].setFillColor(sf::Color::Black);
		button[selectedItemIndex].setOutlineColor(sf::Color::Black);
		selectedItemIndex++;
		buttontext[selectedItemIndex].setFillColor(sf::Color::Red);
		button[selectedItemIndex].setOutlineColor(sf::Color::Red);
	}
}
void MainMenu::PauseButtons(float width, float height)
{
	std::cout << "obiekt pauzy" << std::endl;
	font.loadFromFile("./assets/BigSmoke.ttf");

	title.setFont(font);
	title.setFillColor(sf::Color::Black);
	//title.setFillColor(sf::Color::White);
	title.setCharacterSize(100);
	title.setString("PAUZA");
	title.setPosition(sf::Vector2f(250, 50));

	std::vector<sf::FloatRect> textbounds;
	std::vector<sf::FloatRect> buttonbounds;

	//TEKST PRZYCISKU GRAJ
	buttontext[0].setString("WZNOW");
	buttontext[1].setString("WYJSCIE");
	for(int i = 0; i < 2; i++)
	{
		buttontext[i].setFont(font);
		buttontext[i].setFillColor(sf::Color::Black);
		buttontext[i].setCharacterSize(70);
		buttontext[i].setPosition(sf::Vector2f(400, (320 * (i + 1)) + 50));
		textbounds.emplace_back(buttontext[i].getLocalBounds());
		buttontext[i].setOrigin(sf::Vector2f(textbounds[i].left + textbounds[i].width / 2, textbounds[i].top + textbounds[i].height / 2));

		button[i].setSize(sf::Vector2f(textbounds[i].width + 5.0, 80));
		buttonbounds.emplace_back(button[i].getLocalBounds());

		button[i].setFillColor(sf::Color(255, 247, 226));
		button[i].setOutlineColor(sf::Color::Black);
		button[i].setOutlineThickness(5);
		button[i].setOrigin(sf::Vector2f(buttonbounds[i].left + buttonbounds[i].width / 2, buttonbounds[i].top + buttonbounds[i].height / 2));
		button[i].setPosition(sf::Vector2f(400, (320 * (i + 1)) + 50));
	}
	pauseBackground.setFillColor(sf::Color(0, 0, 0, 1));
	pauseBackground.setSize(sf::Vector2f(width, height));
	pauseBackground.setPosition(sf::Vector2f(0, 0));
	selectedItemIndex = 0;

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
	Background background;
	background.ready_background_texture();
	MenuButtons(800,1000);

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
									std::cout << "wybrano opcj� GRAJ" << std::endl;
									break;
								case _OPCJE:
									std::cout << "wybrano opcj� OPCJE" << std::endl;
									break;
								case _WYJSCIE:
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