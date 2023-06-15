#include "player.h"
#include "Game.h"

player::player()
{
	setParameters();
}
void player::update( std::vector<platform*> *platformy, std::vector<bomb*> *bomby , std::vector<coin*> *monety , std::vector<heart*> *serca ,sf::Event event)
{
	//  // sprawdzilismy w funckji collision czy kolizja wystepuje z ruchom¹ platforma. jezeli tak to move_platforma jest rozna od zera a za razem gracz "jedzie" z platforma
	move_x(platformy);
	move_y(platformy , event);
	if_przegrana(bomby , platformy); // sprawdzanie czy gracz zyje 
	animate(); // po zakonczonym ruszaniu gracza animujemy go na podstawie zmienionej pozycji 
	add_score(monety); // sprawdza kolizje z monetami nastepnie zwieksza wynik gracza 
	update_lives(serca); // sprawdza kolizje z sercami i odpowiednio dodaje zycia 
}
void player::setParameters()
{
	if(!Run_t.loadFromFile("assets/Pink Man/Run (32x32).png"))
	{
		std::cout << "Nie za³adowano grafiki gracza" << std::endl;
	}
	if (!Fall_t.loadFromFile("assets/Pink Man/Fall (32x32).png"))
	{ 
		std::cout << "Nie za³adowano grafiki gracza" << std::endl;
	}
	if (!Idle_t.loadFromFile("assets/Pink Man/Idle (32x32).png"))
	{
		std::cout << "Nie za³adowano grafiki gracza" << std::endl;
	}
	if (!Jump_t.loadFromFile("assets/Pink Man/Jump (32x32).png"))
	{
		std::cout << "Nie za³adowano grafiki gracza" << std::endl;
	}
	if (!DoubleJump_t.loadFromFile("assets/Pink Man/Double Jump (32x32).png"))
	{
		std::cout << "Nie za³adowano grafiki gracza" << std::endl;
	}
	setPosition(sf::Vector2f(2050, 790));
	setTexture(Run_t);
	setScale(2, 2);
	setTextureRect(sf::IntRect(0, 0, 32, 32));
	v_gracz.y = 8.2; 
	grawitacja = sf::Vector2f(0, 0.3);
	stan = alive;
	kierunek = stand;
	player_jump = nothing; 
	score = 0;
	setOrigin(16, 0);
	zycia_gracza = 1;
	numer_klatki_animacji = 0;
	numer_klatki_animacji_doublejump = 0;
	for(int i = 0; i < 11; i++)
	{
		klatki_animacji.emplace_back(sf::IntRect(0 + 32 * i, 0, 32, 32));
	}
	for (int i = 0; i < 6; i++)
	{
		klatki_animacji_doublejump.emplace_back(sf::IntRect(0 + 32 * i, 0, 32, 32));
	}
}
sf::Vector2f player::sprawdz_klaw() // na podstawie inputu gracza rusza go w osi X
{
	sf::Vector2f predkosc(0, 0);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		predkosc.x = -4;
		kierunek = left;

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		predkosc.x = 4;
		kierunek = right; 
	}
	else
	{
		kierunek = stand; 
	}
	return predkosc;
}


bool player::collision(std::vector<platform*> *platformy, bool blokada) // funkcja sprawdzajaca kolizje miedzy graczem a obiektami 
{
	move_platform = sf::Vector2f(0, 0); 
	bool kolizja = false; 
	for (auto platforma : *platformy)
	{	
		 if (getGlobalBounds().intersects(platforma->getGlobalBounds()) && v_gracz.y >= 0 && getGlobalBounds().top + getGlobalBounds().height - 19*grawitacja.y -3  <= platforma->getGlobalBounds().top)
		{
			move_platform = platforma->return_speed();
			kolizja = true;	
		}
		 else if (getGlobalBounds().intersects(platforma->getGlobalBounds()) && v_gracz.y < 0)
		 {
			 move(0, 0.2); // debugging , tzn jezeli gracz znajduje sie w platformie oraz spada to zamiast zatrzymac sie to nie zablokuje sie 
		 }
	}
	return kolizja; 
}


void player::if_przegrana(std::vector<bomb*> *bomby , std::vector<platform*> *platformy) // sprwadza kolizje miedzy graczem a bombami
{   
	if(platformy->size()>0)
	if (getGlobalBounds().top + getGlobalBounds().height > platformy->front()->getPosition().y + 300)
	{
		zycia_gracza = 0; 
	}
	for (auto &x : *bomby)
	{
		if (getGlobalBounds().intersects(x->getGlobalBounds()) && zycia_gracza == 1)
		{
			zycia_gracza = 0; // musi byc ten warunek poniewaz animacja wybychu bomby znajduje sie w samym obiekcie bomby
			// wiec jezeli ja usuniemy to nie bedzie mozna wykonac animacji poniewaz nie bedzie obiektu 
		}
		else if (getGlobalBounds().intersects(x->getGlobalBounds()) )
		{
			zycia_gracza = zycia_gracza - 1; 
			auto element = std::find(bomby->begin(), bomby->end(), x);
			bomby->erase(element); 
		}
	}
	if(zycia_gracza == 0)
		stan = dead;
}

player::status player::get_status()
{
	return stan; 
}

void player::animate() // funkcja animate pobiera kierunek ruchu gracza , tzn left lub right nastepnie szykuje klatki animacji 
{
	setTexture(Run_t);
	if (clock.getElapsedTime().asSeconds() > czas_animacji.asSeconds() + 0.10)
	{
		numer_klatki_animacji++;
		numer_klatki_animacji_doublejump++;
		czas_animacji = clock.getElapsedTime();
	}
	if (numer_klatki_animacji == 11)
	{
		clock.restart();
		czas_animacji = clock.getElapsedTime();
		numer_klatki_animacji = 0;
	}
	if (numer_klatki_animacji_doublejump == 6)
	{
		numer_klatki_animacji_doublejump = 0; 
	}
	if (kierunek == left || kierunek == right || kierunek == stand)
	{
		//setTexture(Run_t); 
		setTextureRect(klatki_animacji[numer_klatki_animacji]);
	}
	if(kierunek == left || kierunek == right)
               setTexture(Run_t);
	if (kierunek == left && getScale().x == 2) // obracanie sprita w lewo 
	{
			setScale(-2, 2);
	}
	else  if (kierunek == right && getScale().x == -2) // obracanie sprita w prawo 
	{
			setScale(2, 2);
	}			
	else if(kierunek == stand) // gdy stoi 
	{
		setTexture(Idle_t); 
		//setTextureRect(sf::IntRect(0, 0, 32, 30));
	}
	
	if (player_jump == fall) // gdy spada
	{
		setTextureRect(sf::IntRect(0, 0, 32, 32));
		setTexture(Fall_t); 
	}
	else if (player_jump == jump) // zmienna player_jump umozliwia rozrozniania w funkcji akcji gracza
	{
		setTextureRect(sf::IntRect(0, 0, 32, 32));
		setTexture(Jump_t); 
	}
	if (player_jump == double_jump)
	{
		setTexture(DoubleJump_t); 
		setTextureRect(klatki_animacji_doublejump[numer_klatki_animacji_doublejump]); 
	}
}

void player::move_x(std::vector<platform*> *platformy)
{
	pozycja = getPosition();
	move(sprawdz_klaw());// ruch jest rozpatrywany osobno w plaszczyznie x oraz y , tutaj jest plaszczyzna X 
	move(move_platform);
	if (collision(platformy, true) == true) // najpierw ruszamy w plaszyznie x , sprawdzamy kolizje. jezeli wystapila to cofamy obiekt
	{                                       // do momentu przed kolizja 
		setPosition(pozycja);

	}
	v_gracz.x = 0; // po zakonczonym ruchu zerujemy predkosc gracza na osi x 
}

void player::move_y(std::vector<platform*> *platformy , sf::Event event)
{
	pozycja = getPosition();
	if (v_gracz.y < 8)
	{
		v_gracz += grawitacja;
	}
	move(v_gracz);// tutaj to samo tylko dla osi y 
	move(move_platform);
	if (collision(platformy, false) == true)
	{    setPosition(pozycja);
	     v_gracz.y = 8.5; 
		if (collision_clock.getElapsedTime().asSeconds() < 1 && event.key.code == sf::Keyboard::W)
		{   
			v_gracz.y -= 30;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{								 
					v_gracz.y -= 22;
		}
		
	}      
	 if (v_gracz.y > 0 && v_gracz.y < 8.3)
	{
		player_jump = fall; // jezeli kolizja nie wystapila oraz predkosc gracza jest wieksza od zera to znaczy , ze gracz spada
		collision_clock.restart();
	}
	 else if (v_gracz.y < 0 && v_gracz.y > -13.5)
	{
		player_jump = jump;
	}
	 else if (v_gracz.y < -13.5)
	 {
		 player_jump = double_jump;
	 }
	 else
	{
		player_jump = nothing; 
	}
	
}

void player::add_score(std::vector<coin*> *monety)//dodawanie wyniku gracza przez zbieranie monet
{
	for (auto& m : *monety)
	{
		if (this->getGlobalBounds().intersects(m->getGlobalBounds()))
		{
			score++; 
			auto element = std::find(monety->begin(), monety->end(), m);
			if (element != monety->end())
			{
				delete(m);
				monety->erase(element);
			}
		}
	}
}

void player::update_lives(std::vector<heart*> *serca) //aktualizacja stanu serc 
{
	for (auto& s : *serca)
	{
		if (this->getGlobalBounds().intersects(s->getGlobalBounds()) && zycia_gracza < 3)
		{
			auto x = std::find(serca->begin(), serca->end(), s);
			if (x != serca->end())
			{
				serca->erase(x);
				zycia_gracza++;
			}
		}
	}
}

int player::return_score()//zwracanie wyniku gracza
{
	return score;
}


int player::return_lives()//zwracanie liczby zyc
{
	return zycia_gracza; 
}

void player::set_texture(sf::Texture tekstura)//ustawianie tekstury gracza na nowo po game over
{
	setTexture(tekstura);
}
