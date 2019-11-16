#include "Game.h"

Game::Game(sf::RenderWindow &win)
{
	if (!tex_tiles.loadFromFile(TEXPATH_TILES))
	{
		win.close();
		getchar();
	}
	else
		map = new Mapa(tex_tiles);
}

Game::~Game()
{
	delete map;
	map = nullptr;
}

void Game::handleEvents(sf::RenderWindow &win)
{
	sf::Event ev;
	while (win.pollEvent(ev))
	{
		switch (ev.type)
		{
		case sf::Event::Closed:
			win.close();
			break;
		default:
			break;
		}
	}
}

void Game::update()
{

}

void Game::draw(sf::RenderWindow &win)
{
	map->draw(win);
}