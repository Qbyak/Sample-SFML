#include "MainMenu.h"
#include "Game.h"

MainMenu::MainMenu(float width, float height)
{
	font.loadFromFile("./assets/BigSmoke.ttf");
	
	title.setFont(font);
	title.setFillColor(sf::Color::Black);
	//title.setFillColor(sf::Color::White);
	title.setCharacterSize(120);
	title.setString("Cloudy Tower");
	title.setPosition(sf::Vector2f(5,50));
	std::vector<sf::FloatRect> textbounds;
	std::vector<sf::FloatRect> buttonbounds;

//TEKST PRZYCISKU GRAJ
	_mainmenu[0].setString("GRAJ");
	_mainmenu[1].setString("OPCJE");
	_mainmenu[2].setString("WYJSCIE");
	for(int i=0; i < MAX_NUMBER_OF_BUTTONS; i++)
	{
		_mainmenu[i].setFont(font);
		_mainmenu[i].setFillColor(sf::Color::Black);
		_mainmenu[i].setCharacterSize(70);
		_mainmenu[i].setPosition(sf::Vector2f(400, (250 * (i+1))+20));
		textbounds.emplace_back(_mainmenu[i].getLocalBounds());
		_mainmenu[i].setOrigin(sf::Vector2f(textbounds[i].left + textbounds[i].width / 2, textbounds[i].top + textbounds[i].height / 2));

		button[i].setSize(sf::Vector2f(textbounds[i].width + 5.0, 80));
		buttonbounds.emplace_back(button[i].getLocalBounds());
		
		button[i].setFillColor(sf::Color(255, 247, 226));
		button[i].setOutlineColor(sf::Color::Black);
		button[i].setOutlineThickness(5);
		button[i].setOrigin(sf::Vector2f(buttonbounds[i].left + buttonbounds[i].width / 2, buttonbounds[i].top + buttonbounds[i].height / 2));
		button[i].setPosition(sf::Vector2f(400, (250 * (i + 1)) + 20));
	}
	
	selectedItemIndex = 2;
	
}
MainMenu::~MainMenu()
{
}
void MainMenu::draw(sf::RenderWindow& window)
{
	window.draw(title);
	for(int i = 0; i < MAX_NUMBER_OF_BUTTONS; i++)
	{
		window.draw(button[i]);
		window.draw(_mainmenu[i]);
	}
	window.display();
}

void MainMenu::MoveUp()
{
	if(selectedItemIndex - 1 >= 0)
	{
		_mainmenu[selectedItemIndex].setFillColor(sf::Color::Black);
		button[selectedItemIndex].setOutlineColor(sf::Color::Black);
		selectedItemIndex--;
		_mainmenu[selectedItemIndex].setFillColor(sf::Color::Red);
		button[selectedItemIndex].setOutlineColor(sf::Color::Red);
	}
}

void MainMenu::MoveDown()
{
	if(selectedItemIndex + 1 < MAX_NUMBER_OF_BUTTONS)
	{
		_mainmenu[selectedItemIndex].setFillColor(sf::Color::Black);
		button[selectedItemIndex].setOutlineColor(sf::Color::Black);
		selectedItemIndex++;
		_mainmenu[selectedItemIndex].setFillColor(sf::Color::Red);
		button[selectedItemIndex].setOutlineColor(sf::Color::Red);
	}
}


enum MainMenu::buttons
{
	_GRAJ,
	_OPCJE,
	_WYJSCIE

};



void MainMenu::Play(sf::RenderWindow &window)
{
	//Background::ready_game();

	MainMenu::buttons button = MainMenu::buttons::_OPCJE;
	MainMenu menu(window.getSize().x, window.getSize().y);

	bool petla=true;

  while(petla)
  {
	
		 
		sf::Event event;
		
		while(window.pollEvent(event))
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
							menu.MoveUp();
							break;
							}
						case sf::Keyboard::Down:
							{
							if(button == _OPCJE)
								button=_WYJSCIE;
							else if(button == _GRAJ)
								button = _OPCJE;
							menu.MoveDown();
							break;
							}
						case sf::Keyboard::Return:
							switch(button)
							{
								case _GRAJ:
									petla=false;
									std::cout << "Play button has been pressed" << std::endl;
									break;
								case _OPCJE:
									std::cout << "Option button has been pressed" << std::endl;
									break;
								case _WYJSCIE:
									window.close();
									break;
							}

							break;
					}
			}
			
		}
		
		menu.draw(window);
		window.display();
	
  }
}