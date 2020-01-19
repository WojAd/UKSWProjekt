#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Menu.h"

int main() {

	const sf::VideoMode resolution = sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT);
	const sf::String game_name = "Pacman";

	sf::RenderWindow window(resolution, game_name);
	window.setFramerateLimit(60);
	sf::Clock clk;
	short frames = 0;

	bool is_game = false;

	Menu m(window);
	Game g(window);

	while (window.isOpen())
	{
		if (is_game)
		{
			g.handleEvents();
			g.update();
			g.draw();
		}
		else
		{
			m.handleEvents();
			m.update();
			m.draw();

			if (m.go_reset)
			{
				m.go_reset = false;
				g.reset_game();
			}
		}

		if (m.go_to_game)
		{
			m.go_to_game = false;
			is_game = true;
		}
		else if (g.go_to_menu)
		{
			g.go_to_menu = false;
			is_game = false;
		}

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