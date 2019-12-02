//TEST
//Test 2
#include <SFML/Graphics.hpp>
#include "Game.h"

int main() {
	
	const sf::VideoMode resolution = sf::VideoMode(1024, 760);
	const sf::String game_name = "Pacman";

	sf::RenderWindow window(resolution, game_name);
	window.setFramerateLimit(60);

	Game g(window);
	while (window.isOpen())
	{
		g.handleEvents();
		g.update();
		g.draw();

		window.display();
	}

	return 0;
}