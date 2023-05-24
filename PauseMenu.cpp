#include "PauseMenu.h"
PauseMenu::PauseMenu(float width, float height)
{
	font.loadFromFile("./assets/BigSmoke.ttf");

	title.setFont(font);
	title.setFillColor(sf::Color::Black);
	//title.setFillColor(sf::Color::White);
	title.setCharacterSize(100);
	title.setString("PAUZA");
	title.setPosition(sf::Vector2f(250, 50));

	pausemenu[0].setFont(font);
	pausemenu[0].setFillColor(sf::Color::Black);

	pausemenu[0].setCharacterSize(70);
	pausemenu[0].setString("WZNOW");
	sf::FloatRect t1 = pausemenu[0].getLocalBounds();

	pausemenu[0].setOrigin(sf::Vector2f(t1.left + t1.width / 2, t1.top + t1.height / 2));
	pausemenu[0].setPosition(sf::Vector2f(400, 1000 / (MAX_NUMBER_OF_PAUSE_BUTTONS + 1) * 1));

	button[0].setSize(sf::Vector2f(t1.width+5.0, 80));
	sf::FloatRect b1 = button[0].getLocalBounds();

	button[0].setOrigin(sf::Vector2f(b1.left + b1.width / 2, b1.top + b1.height / 2));
	button[0].setPosition(sf::Vector2f(400, 1000 / (MAX_NUMBER_OF_PAUSE_BUTTONS + 1) * 1));
	button[0].setFillColor(sf::Color(255, 247, 226));
	button[0].setOutlineColor(sf::Color::Black);
	button[0].setOutlineThickness(5);

	pausemenu[1].setFont(font);
	pausemenu[1].setFillColor(sf::Color::Black);

	pausemenu[1].setCharacterSize(70);
	pausemenu[1].setString("WYJSCIE");
	sf::FloatRect t2 = pausemenu[1].getLocalBounds();
	pausemenu[1].setOrigin(sf::Vector2f(t2.left + t2.width / 2, t2.top + t2.height / 2));
	pausemenu[1].setPosition(sf::Vector2f(400, 1000 / (MAX_NUMBER_OF_PAUSE_BUTTONS + 1) * 2));


	button[1].setSize(sf::Vector2f(t2.width + 5.0, 80));
	sf::FloatRect b2 = button[1].getLocalBounds();

	button[1].setOrigin(sf::Vector2f(b2.left + b2.width / 2, b2.top + b2.height / 2));
	button[1].setPosition(sf::Vector2f(400, 1000/ (MAX_NUMBER_OF_PAUSE_BUTTONS + 1) * 2));
	button[1].setFillColor(sf::Color(255, 247, 226));
	button[1].setOutlineColor(sf::Color::Black);
	button[1].setOutlineThickness(5);

	selectedItemIndex = 0;

}
void PauseMenu::draw(sf::RenderWindow& window)
{
	window.draw(title);
	for(int i = 0; i < MAX_NUMBER_OF_PAUSE_BUTTONS; i++)
	{
		window.draw(button[i]);
		window.draw(pausemenu[i]);
	}
}
void PauseMenu::MoveUp()
{
	if(selectedItemIndex - 1 >= 0)
	{
		pausemenu[selectedItemIndex].setFillColor(sf::Color::Black);
		button[selectedItemIndex].setOutlineColor(sf::Color::Black);
		selectedItemIndex--;
		pausemenu[selectedItemIndex].setFillColor(sf::Color::Red);
		button[selectedItemIndex].setOutlineColor(sf::Color::Red);
	}
}
void PauseMenu::MoveDown()
{
	if(selectedItemIndex + 1 < MAX_NUMBER_OF_PAUSE_BUTTONS)
	{
		pausemenu[selectedItemIndex].setFillColor(sf::Color::Black);
		button[selectedItemIndex].setOutlineColor(sf::Color::Black);
		selectedItemIndex++;
		pausemenu[selectedItemIndex].setFillColor(sf::Color::Red);
		button[selectedItemIndex].setOutlineColor(sf::Color::Red);
	}
}
void PauseMenu::Play(sf::RenderWindow& window)
{
	bool pauza=true;
	PauseMenu pause(window.getSize().x, window.getSize().y);
	while(pauza)
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
							pause.MoveUp();
							break;

						case sf::Keyboard::Down:
							pause.MoveDown();
							break;

						case sf::Keyboard::Return:
							switch(pause.GetPressedItem())
							{
								case 0:
									pauza=!pauza;
									std::cout << "Play button has been pressed" << std::endl;
									break;
								case 1:
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


		pause.draw(window);

		window.display();
	}
}