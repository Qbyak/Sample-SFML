#include "MainMenu.h"

MainMenu::MainMenu(float width, float height)
{
	font.loadFromFile("./assets/BigSmoke.ttf");
	
	title.setFont(font);
	title.setFillColor(sf::Color::Black);
	title.setFillColor(sf::Color::White);
	title.setCharacterSize(120);
	title.setString("Cloudy Tower");
	title.setPosition(sf::Vector2f(5,50));

	_mainmenu[0].setFont(font);
	_mainmenu[0].setFillColor(sf::Color::Black);
	
	_mainmenu[0].setCharacterSize(70);
	_mainmenu[0].setString("GRAJ");
	sf::FloatRect t1=_mainmenu[0].getLocalBounds();

	_mainmenu[0].setOrigin(sf::Vector2f(t1.left + t1.width/2,t1.top+t1.height/2));
	_mainmenu[0].setPosition(sf::Vector2f(400, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));

	button[0].setSize(sf::Vector2f(160,80));
	sf::FloatRect b1 = button[0].getLocalBounds();

	button[0].setOrigin(sf::Vector2f(b1.left + b1.width / 2, b1.top + b1.height / 2));
	button[0].setPosition(sf::Vector2f(400, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));
	button[0].setFillColor(sf::Color(255,247,226));
	button[0].setOutlineColor(sf::Color::Black);
	button[0].setOutlineThickness(5);

	_mainmenu[1].setFont(font);
	_mainmenu[1].setFillColor(sf::Color::Black);
	
	_mainmenu[1].setCharacterSize(70);
	_mainmenu[1].setString("OPCJE");
	sf::FloatRect t2 = _mainmenu[1].getLocalBounds();
	_mainmenu[1].setOrigin(sf::Vector2f(t2.left+t2.width / 2,t2.top+ t2.height / 2));
	_mainmenu[1].setPosition(sf::Vector2f(400, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));


	button[1].setSize(sf::Vector2f(190, 80));
	sf::FloatRect b2 = button[1].getLocalBounds();

	button[1].setOrigin(sf::Vector2f(b2.left + b2.width / 2, b2.top + b2.height / 2));
	button[1].setPosition(sf::Vector2f(400, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));
	button[1].setFillColor(sf::Color(255, 247, 226));
	button[1].setOutlineColor(sf::Color::Black);
	button[1].setOutlineThickness(5);

	_mainmenu[2].setFont(font);
	_mainmenu[2].setFillColor(sf::Color::Black);
	//_mainmenu[2].setFillColor(sf::Color::White);
	_mainmenu[2].setCharacterSize(70);
	_mainmenu[2].setString("WYJSCIE");
	sf::FloatRect t3 = _mainmenu[2].getLocalBounds();
	_mainmenu[2].setOrigin(sf::Vector2f(t3.left + t3.width / 2,t3.top+ t3.height / 2));
	_mainmenu[2].setPosition(sf::Vector2f(400, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));

	button[2].setSize(sf::Vector2f(260, 80));
	sf::FloatRect b3 = button[2].getLocalBounds();

	button[2].setOrigin(sf::Vector2f(b3.left + b3.width / 2, b3.top + b3.height / 2));
	button[2].setPosition(sf::Vector2f(400, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));
	button[2].setFillColor(sf::Color(255, 247, 226));
	button[2].setOutlineColor(sf::Color::Black);
	button[2].setOutlineThickness(5);

	selectedItemIndex = 0;
	
}
MainMenu::~MainMenu()
{
}
void MainMenu::draw(sf::RenderWindow& window)
{
	window.draw(title);
	for(int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(button[i]);
		window.draw(_mainmenu[i]);
	}
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
	if(selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		_mainmenu[selectedItemIndex].setFillColor(sf::Color::Black);
		button[selectedItemIndex].setOutlineColor(sf::Color::Black);
		selectedItemIndex++;
		_mainmenu[selectedItemIndex].setFillColor(sf::Color::Red);
		button[selectedItemIndex].setOutlineColor(sf::Color::Red);
	}
}
void MainMenu::ready_game()
{
	if(!tlo1.loadFromFile("assets/parallax-mountain-bg.png"))
	{
		std::cout << "nie zaladowano tla";
	}
	tlo_s.setTexture(tlo1);
	tlo_s.setScale(3, 5);
	tlo_s.setPosition(0, 0);
	if(!tlo2.loadFromFile("assets/parallax-mountain-foreground-trees.png"))
	{
		std::cout << "nie zaladowano tla";
	}
	tlo_s2.setTexture(tlo2);
	tlo_s2.setPosition(sf::Vector2f(0, 350));
	tlo_s2.setScale(sf::Vector2f(4, 4));
	if(!tlo3.loadFromFile("assets/parallax-mountain-montain-far.png"))
	{
		std::cout << "nie zaladowano tla";
	}
	tlo_s3.setTexture(tlo3);
	tlo_s3.setPosition(sf::Vector2f(0, -100));
	tlo_s3.setScale(sf::Vector2f(4, 7));
	if(!tlo4.loadFromFile("assets/parallax-mountain-trees.png"))
	{
		std::cout << "nie zaladowano tla";
	}
	tlo_s4.setTexture(tlo4);
	tlo_s4.setPosition(sf::Vector2f(0, 400));
	tlo_s4.setScale(sf::Vector2f(2, 4));
	if(!tlo5.loadFromFile("assets/parallax-mountain-mountains.png"))
	{
		std::cout << "nie zaladowano tla";
	}
	tlo_s5.setTexture(tlo5);
	tlo_s5.setPosition(sf::Vector2f(0, 0));
	tlo_s5.setScale(sf::Vector2f(6, 6));
}
void MainMenu::draw_tlo(sf::RenderWindow& window)
{
	window.draw(tlo_s);
	window.draw(tlo_s5);
	window.draw(tlo_s3);
	window.draw(tlo_s4);
	window.draw(tlo_s2);
}
void MainMenu::Odpalaj()
{
	ready_game();
	sf::RenderWindow window(sf::VideoMode(800,1000), "Main Menu");

	MainMenu menu(window.getSize().x, window.getSize().y);
	
	while(window.isOpen())
	{
		sf::Event event;
		
		draw_tlo(window);
		while(window.pollEvent(event))
		{
			switch(event.type)
			{
				case sf::Event::KeyReleased:
					switch(event.key.code)
					{
						case sf::Keyboard::Up:
							menu.MoveUp();
							break;

						case sf::Keyboard::Down:
							menu.MoveDown();
							break;

						case sf::Keyboard::Return:
							switch(menu.GetPressedItem())
							{
								case 0:
									
									std::cout << "Play button has been pressed" << std::endl;
									break;
								case 1:
									std::cout << "Option button has been pressed" << std::endl;
									break;
								case 2:
									window.close();
									break;
							}

							break;
					}

					break;
				case sf::Event::Closed:
					window.close();

					break;

			}
		}

		
		menu.draw(window);

		window.display();
	}
}