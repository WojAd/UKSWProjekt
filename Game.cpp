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

	pacman = new Pacman(PACMAN_START_X, PACMAN_START_Y, PACMAN_MAX_LIVES, win.getView().getSize().x, win.getView().getSize().y);

	if (!tex_life.loadFromFile(TEXPATH_LIFE))
	{
		win.close();
		getchar();
	}
	else
		life = new sf::Sprite(tex_life);
}

Game::~Game()
{
	delete map;
	map = nullptr;
	delete pacman;
	pacman = nullptr;
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
	pacman->update();
}

void Game::draw(sf::RenderWindow &win)
{
	map->draw(win);
	win.draw(*pacman);

	for (short i = 0; i < 3/*pacman.getLives()*/; i++)
	{
		life->setPosition(sf::Vector2f(i*LIFE_WIDTH, 50));
		win.draw(*life);
	}
}