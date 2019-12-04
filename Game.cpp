#include "Game.h"

Game::Game(sf::RenderWindow &win)
{
	this->win = &win;
	state = READY;

	if (!fnt_default.loadFromFile(FONTPATH_DEFAULT))
	{
		win.close();
		getchar();
	}
	else
	{
		txt_points.setFont(fnt_default);
		txt_points.setCharacterSize(TXT_POINTS_SIZE);
		txt_points.setPosition(sf::Vector2f(TXT_POINTS_X, TXT_POINTS_Y));
		txt_points.setString(L"Punkty: ");
		txt_points.setFillColor(sf::Color::Yellow);
	}


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
		ghosts.push_back(*(new Ghost(this->win->getView().getSize().x / 2 - 40 + i*40, this->win->getView().getSize().y/2, map)));
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
	switch (state)
	{
	case READY:
		state = RUNNING;// CHANGE!
	case RUNNING:
		game_running();
		break;
	case LOSE_LIFE:
		lose_life();
		break;
	case GAME_OVER:
		game_over();
		break;
	default:
		break;
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

	win->draw(txt_points);
	for (short i = 0; i < pacman->getLives(); i++)
	{
		life->setPosition(sf::Vector2f(i*LIFE_WIDTH + LIFE_X, LIFE_Y));
		win->draw(*life);
	}
}

/*----------------------*/
/*Game private functions*/
/*----------------------*/
void Game::game_running()
{
	pacman->update();
	for (auto &i : ghosts)
	{
		i.update(pacman->getPosition().x, pacman->getPosition().y);
	}

	//Engine mechanics
	for (auto &i : ghosts)
	{
		/*if(i.getSprite()getGlobalBounds().intersects(pacman.getSprtie().getGlobalBounds()))
		{
			state = LOSE_LIFE;
			pacman->setLives(--);
		}*/
	}
}

void Game::lose_life()
{
	if (pacman->getLives() <= 0)
		state = GAME_OVER;
}

void Game::game_over()
{
	//...
}