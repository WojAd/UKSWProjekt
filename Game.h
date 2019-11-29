#ifndef GAME_H
#define GAME_H

#include "FilePaths.h"
#include "mapa.h"
#include "pacman.h"
#include "duch.h"

#define PACMAN_START_X 100
#define PACMAN_START_Y 100
#define PACMAN_MAX_LIVES 3

#define GHOST_AMOUNT 2

#define LIFE_WIDTH 30
#define LIFE_HEIGHT 30

class Game
{
private:
	//Textures
	sf::Texture tex_tiles;
	//sf::Texture tex_pacman;
	sf::Texture tex_life;

	Mapa *map = nullptr;
	Pacman *pacman = nullptr;
	sf::Sprite *life = nullptr;
	std::vector<Ghost> ghosts;
public:
	Game(sf::RenderWindow &win);
	~Game();

	void handleEvents(sf::RenderWindow &win);
	void update();
	void draw(sf::RenderWindow &win);
};
#endif