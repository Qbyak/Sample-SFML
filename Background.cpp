#include "Background.h"

void Background::draw_tlo(sf::RenderWindow& window) // rysowanie tla 
{
	window.draw(tlo_s);
	window.draw(tlo_s5);
	window.draw(tlo_s3);
	window.draw(tlo_s4);
	window.draw(tlo_s2);
}
void Background::ready_game()
{

}