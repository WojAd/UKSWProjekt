#ifndef GAME_H
#define GAME_H

#include "mapa.h"

class Game
{
private:
	Mapa map;
public:
	Game();
	~Game();

	void init();
	void handleEvents();
	void update();
	void draw(sf::RenderWindow &win);
};
#endif