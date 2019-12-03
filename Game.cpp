#include "Game.h"

Game::Game(sf::RenderWindow &win)
{
	this->win = &win;

	if (!tex_tiles.loadFromFile(TEXPATH_TILES))
	{
		win.close();
		getchar();
	}
	else
		map = new Mapa(tex_tiles);

	pacman = new Pacman(PACMAN_START_X, PACMAN_START_Y, PACMAN_MAX_LIVES, win.getView().getSize().x, win.getView().getSize().y, map);
	for (short i = 0; i < GHOST_AMOUNT; i++)
	{
		ghosts.push_back(*(new Ghost(this->win->getView().getSize().x / 2 - 40 + i*40, this->win->getView().getSize().y/2)));
	}

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
	ghosts.clear();
}

void Game::handleEvents()
{
	sf::Event ev;
	while (win->pollEvent(ev))
	{
		switch (ev.type)
		{
		case sf::Event::Closed:
			win->close();
			break;
		default:
			break;
		}
	}
}

void Game::update()
{
	pacman->update();
	for (auto &i : ghosts)
	{
		i.update();
	}

	//Engine mechanics
	for (auto &i : ghosts)
	{
		//if(i.getSprite()getGlobalBounds().intersects(pacman.getSprtie().getGlobalBounds()))
			//lose_life();
	}
}

void Game::draw()
{
	win->clear();

	map->draw(*win);
	win->draw(*pacman);

	for (auto &i : ghosts)
	{
		win->draw(i);
	}

	for (short i = 0; i < 3/*pacman.getLives()*/; i++)
	{
		life->setPosition(sf::Vector2f(i*LIFE_WIDTH, 50));
		win->draw(*life);
	}
}