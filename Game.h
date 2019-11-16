#ifndef GAME_H
#define GAME_H

#include "FilePaths.h"
#include "mapa.h"

class Game
{
private:
	//Textures
	sf::Texture tex_tiles;
	sf::Texture tex_pacman;

	Mapa *map = nullptr;
public:
	Game(sf::RenderWindow &win);
	~Game();

	void handleEvents(sf::RenderWindow &win);
	void update();
	void draw(sf::RenderWindow &win);
};
#endif