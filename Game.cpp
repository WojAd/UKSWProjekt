#include "Game.h"

Game::Game(sf::RenderWindow &win)
{
	this->win = &win;
	_paused = false;
	sf::Vector2f resolution = win.getView().getSize();
	state = READY;

	if (!fnt_default.loadFromFile(FONTPATH_DEFAULT))
	{
		win.close();
		getchar();
	}
	else
	{
		points = 0;
		txt_points.setFont(fnt_default);
		txt_points.setCharacterSize(TXT_POINTS_SIZE);
		txt_points.setPosition(sf::Vector2f(TXT_POINTS_X, TXT_POINTS_Y));
		txt_points.setFillColor(sf::Color::Yellow);
		txt_points.setString(L"Pkt: " + std::to_string(points));

		txt_gameover.setFont(fnt_default);
		txt_gameover.setCharacterSize(TXT_GAMEOVER_SIZE);
		txt_gameover.setString(L"GAME OVER");
		txt_gameover.setFillColor(sf::Color::Blue);
		sf::Vector2f txt_go_size;
		txt_go_size.x = txt_gameover.getLocalBounds().left + txt_gameover.getLocalBounds().width;
		txt_go_size.y = txt_gameover.getLocalBounds().top + txt_gameover.getLocalBounds().height;
		txt_gameover.setPosition(resolution.x / 2 - txt_go_size.x / 2, resolution.y / 2 - txt_go_size.y / 2);

		txt_pause.setFont(fnt_default);
		txt_pause.setCharacterSize(TXT_POINTS_SIZE);
		txt_pause.setString(L"PAUZA");
		float txt_p_width;
		txt_p_width = txt_pause.getLocalBounds().left + txt_pause.getLocalBounds().width;
		txt_pause.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - txt_p_width / 2, TXT_PAUSE_Y));
		txt_pause.setFillColor(sf::Color::White);

		pause_background.setSize(sf::Vector2f(BACKGROUND_PAUSE_WIDTH, BACKGROUND_PAUSE_HEIGHT));
		pause_background.setFillColor(sf::Color(25, 25, 25));
		pause_background.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - BACKGROUND_PAUSE_WIDTH / 2, WINDOW_HEIGHT / 2 - BACKGROUND_PAUSE_HEIGHT / 2));

		button_continue = new qiwi::Button(sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT), sf::Vector2f(WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2, BUTTON_CONTINUE_Y));
		button_continue->setTextFont(fnt_default);
		button_continue->setTextCharSize(TXT_POINTS_SIZE);
		button_continue->setIdleColor(sf::Color(128, 128, 128));
		button_continue->setHoverColor(sf::Color(200, 200, 200));
		button_continue->setPressColor(sf::Color(50, 50, 50));
		button_continue->setTextString(L"Wróć do gry");

		button_backtomenu = new qiwi::Button(sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT), sf::Vector2f(WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2, BUTTON_BACKTOMENU_Y));
		button_backtomenu->setTextFont(fnt_default);
		button_backtomenu->setTextCharSize(TXT_POINTS_SIZE);
		button_backtomenu->setIdleColor(sf::Color(128, 128, 128));
		button_backtomenu->setHoverColor(sf::Color(200, 200, 200));
		button_backtomenu->setPressColor(sf::Color(50, 50, 50));
		button_backtomenu->setTextString(L"Powrót do menu");

		button_exit = new qiwi::Button(sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT), sf::Vector2f(WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2, BUTTON_EXIT_Y));
		button_exit->setTextFont(fnt_default);
		button_exit->setTextCharSize(TXT_POINTS_SIZE);
		button_exit->setIdleColor(sf::Color(128, 128, 128));
		button_exit->setHoverColor(sf::Color(200, 200, 200));
		button_exit->setPressColor(sf::Color(50, 50, 50));
		button_exit->setTextString(L"Wyjście");
	}


	if (!tex_tiles.loadFromFile(TEXPATH_TILES))
	{
		win.close();
		getchar();
	}
	else
	{
		map = new Mapa(tex_tiles);
		map->setCoinTile(MAP_WIDTH / 2, MAP_HEIGHT / 2, false);
		map->setCoinTile(MAP_WIDTH / 2 + 1, MAP_HEIGHT / 2, false);
		map->setCoinTile(MAP_WIDTH / 2 - 1, MAP_HEIGHT / 2, false);

		map->setCoinTile(MAP_WIDTH / 2, MAP_HEIGHT / 2 - 1, false);

		sf::Vector2u pacman_tile = map->pixelsToTilecoords(sf::Vector2f(PACMAN_START_X, PACMAN_START_Y));
		map->setCoinTile(pacman_tile.x, pacman_tile.y, false);
	}

	pacman = new Pacman(PACMAN_START_X, PACMAN_START_Y, PACMAN_MAX_LIVES, win.getView().getSize().x, win.getView().getSize().y, map);
	for (short i = 0; i < GHOST_AMOUNT; i++)
	{
		ghosts.push_back(*(new Ghost(this->win->getView().getSize().x / 2 - 40 + i * 40, this->win->getView().getSize().y / 2, map)));
	}

	if (!tex_life.loadFromFile(TEXPATH_LIFE))
	{
		win.close();
		getchar();
	}
	else
		life = new sf::Sprite(tex_life);

	if (!tex_coin.loadFromFile(TEXPATH_COIN))
	{
		win.close();
		getchar();
	}
	else
	{
		coin = new sf::Sprite(tex_coin);
		coin->setOrigin(sf::Vector2f(COIN_WIDTH / 2, COIN_HEIGHT / 2));
	}
}

Game::~Game()
{
	delete map;
	map = nullptr;
	delete pacman;
	pacman = nullptr;
	delete coin;
	coin = nullptr;

	delete button_continue;
	delete button_backtomenu;
	delete button_exit;

	ghosts.clear();
}

void Game::handleEvents()
{
	char_entered = NULL;
	sf::Event ev;
	while (win->pollEvent(ev))
	{
		switch (ev.type)
		{
		case sf::Event::Closed:
			win->close();
			break;
		case sf::Event::TextEntered:
			char_entered = ev.text.unicode;
			break;
		default:
			break;
		}
	}
}

void Game::update()
{
	if (_paused)
		pause_update();
	else
	{
		if (char_entered == 27)
			_paused = !_paused;

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
		case GAME_WON:
			game_win();
			break;
		default:
			break;
		}
	}
}

void Game::draw()
{
	win->clear();

	map->draw(*win);
	draw_coins();
	win->draw(*pacman);

	for (auto &i : ghosts)
	{
		win->draw(i);
	}

	win->draw(txt_points);
	draw_lives();

	if (state == GAME_OVER)
		win->draw(txt_gameover);
	else if (state == GAME_WON)
		win->draw(txt_gameover);

	if (_paused)
	{
		draw_pause();
	}
}

/*----------------------*/
/*Game private functions*/
/*----------------------*/

void Game::draw_coins()
{
	for (short y = 0; y < MAP_HEIGHT; y++)
	{
		for (short x = 0; x < MAP_WIDTH; x++)
		{
			if (this->map->getCoinTile(x, y) == true)
			{
				coin->setPosition(this->map->tilecoordsToPixels(x, y));
				win->draw(*coin);
			}
		}
	}
}

void Game::draw_lives()
{
	for (short i = 0; i < pacman->getLives(); i++)
	{
		life->setPosition(sf::Vector2f(i*LIFE_WIDTH + LIFE_X, LIFE_Y));
		win->draw(*life);
	}
}

/*MAJOR*/
void Game::game_running()
{
	if (map->getCoinQuantity() <= 0)
	{
		state = GAME_WON;
		txt_gameover.setString("GAME WON!");
		frame_time = 0;
	}

	pacman->update();
	if (pacman->getPosition().x <= map->getOffset())
		pacman->setPosition(sf::Vector2f(map->tilecoordsToPixels(MAP_WIDTH - 1, 0).x, pacman->getPosition().y));
	else if (pacman->getPosition().x >= map->tilecoordsToPixels(MAP_WIDTH - 1, 0).x)
		pacman->setPosition(sf::Vector2f(map->tilecoordsToPixels(0, 0).x, pacman->getPosition().y));

	for (auto &i : ghosts)
	{
		i.update(pacman->getPosition().x, pacman->getPosition().y);
	}

	//Engine mechanics
	for (auto &i : ghosts)
	{
		if (i.getSprite().getGlobalBounds().intersects(pacman->getSprite().getGlobalBounds()))
		{
			state = LOSE_LIFE;
			frame_time = 0;
			pacman->setLives(pacman->getLives() - 1);
			pacman->killPacman();
			break;
		}
	}

	sf::Vector2u pacman_tilepos = map->pixelsToTilecoords(pacman->getPosition());
	if (map->getCoinTile(pacman_tilepos.x, pacman_tilepos.y) == true)
	{
		map->setCoinTile(pacman_tilepos.x, pacman_tilepos.y, false);
		points += 10;
		txt_points.setString(L"Pkt: " + std::to_string(points));
	}
}

void Game::lose_life()
{
	pacman->update();

	if (frame_time >= LOSE_LIFE_FRAME_TIME)
	{
		if (pacman->getLives() <= 0)
		{
			state = GAME_OVER;
			txt_gameover.setString("GAME OVER");
		}
		else
		{
			state = RUNNING;

			short j = 0;
			for (auto&i : ghosts)
			{
				i.setPosition(sf::Vector2f(this->win->getView().getSize().x / 2 - TILE_WIDTH + j / GHOST_AMOUNT * 2 * TILE_WIDTH, this->win->getView().getSize().y / 2));
				i.setPosition(sf::Vector2f(this->win->getView().getSize().x / 2 - 40 + j * 40, this->win->getView().getSize().y / 2));
				j++;
			}

			pacman->setPosition(sf::Vector2f(PACMAN_START_X, PACMAN_START_Y));
			pacman->revivePacman();
		}

		frame_time = 0;
	}
	else
	{
		frame_time++;
	}
}

void Game::game_over()
{
	if (frame_time >= LOSE_LIFE_FRAME_TIME)
	{
		go_to_menu = true;
		reset_game();
		frame_time = 0;
	}
	else
	{
		frame_time++;
	}
}

void Game::game_win()
{
	if (frame_time >= LOSE_LIFE_FRAME_TIME)
	{
		win->close();
		frame_time = 0;
	}
	else
	{
		frame_time++;
	}
}

void Game::draw_pause()
{
	win->draw(pause_background);
	win->draw(txt_pause);
	win->draw(*button_continue);
	win->draw(*button_backtomenu);
	win->draw(*button_exit);
}

void Game::pause_update()
{
	if (char_entered == 27)
		_paused = !_paused;

	button_continue->update(*win);
	button_backtomenu->update(*win);
	button_exit->update(*win);

	if (button_continue->clicked())
		_paused = false;
	else if (button_backtomenu->clicked())
		go_to_menu = true;
	else if (button_exit->clicked())
		win->close();
}

void Game::reset_game()
{
	state = RUNNING;
	_paused = false;
	points = 0;

	delete pacman;
	ghosts.clear();

	pacman = new Pacman(PACMAN_START_X, PACMAN_START_Y, PACMAN_MAX_LIVES, win->getView().getSize().x, win->getView().getSize().y, map);
	for (short i = 0; i < GHOST_AMOUNT; i++)
	{
		ghosts.push_back(*(new Ghost(this->win->getView().getSize().x / 2 - 40 + i * 40, this->win->getView().getSize().y / 2, map)));
	}

	delete map;
	map = new Mapa(tex_tiles);
	map->setCoinTile(MAP_WIDTH / 2, MAP_HEIGHT / 2, false);
	map->setCoinTile(MAP_WIDTH / 2 + 1, MAP_HEIGHT / 2, false);
	map->setCoinTile(MAP_WIDTH / 2 - 1, MAP_HEIGHT / 2, false);

	map->setCoinTile(MAP_WIDTH / 2, MAP_HEIGHT / 2 - 1, false);

	sf::Vector2u pacman_tile = map->pixelsToTilecoords(sf::Vector2f(PACMAN_START_X, PACMAN_START_Y));
	map->setCoinTile(pacman_tile.x, pacman_tile.y, false);
}