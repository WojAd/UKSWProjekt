//TEST
//Test 2
#include <SFML/Graphics.hpp>
#include "Game.h"

int main() {
	
	const sf::VideoMode resolution = sf::VideoMode(1200, 720);
	const sf::String game_name = "Pacman";
	sf::RenderWindow window(resolution, game_name);

	Game g(window);
	while (window.isOpen())
	{
		g.handleEvents(window);
		g.update();
		g.draw(window);

		window.display();
	}

	return 0;
}