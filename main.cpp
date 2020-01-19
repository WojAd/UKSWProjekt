//TEST
//Test 2
#include <SFML/Graphics.hpp>
#include "Game.h"

int main() {
	
	const sf::VideoMode resolution = sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT);
	const sf::String game_name = "Pacman";

	sf::RenderWindow window(resolution, game_name);
	window.setFramerateLimit(60);
	sf::Clock clk;
	short frames = 0;

	Game g(window);
	while (window.isOpen())
	{
		g.handleEvents();
		g.update();
		g.draw();

		window.display();

		frames++;
		if (clk.getElapsedTime().asMilliseconds() >= 1000)
		{
			system("cls");
			std::cout << "FPS: " << frames;
			clk.restart();
			frames = 0;
		}
	}

	return 0;
}