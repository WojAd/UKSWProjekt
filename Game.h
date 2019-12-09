#ifndef GAME_H
#define GAME_H

#include "FilePaths.h"
#include "mapa.h"
#include "pacman.h"
#include "duch.h"

#define LOSE_LIFE_FRAME_TIME 120

#define PACMAN_START_X 512
#define PACMAN_START_Y 620
//#define PACMAN_MAX_LIVES 3

#define GHOST_AMOUNT 3

#define LIFE_WIDTH 30
#define LIFE_HEIGHT 30
#define LIFE_X 5
#define LIFE_Y 40

#define TXT_POINTS_X 5
#define TXT_POINTS_Y 5
#define TXT_POINTS_SIZE 18

#define TXT_GAMEOVER_SIZE 72

class Game
{
	enum GAME_STATES
	{
		READY,
		RUNNING,
		LOSE_LIFE,
		GAME_OVER
	};

private:
	sf::RenderWindow *win = nullptr;

	//Textures
	sf::Texture tex_tiles;
	//sf::Texture tex_pacman;
	sf::Texture tex_life;

	//Fonts
	sf::Font fnt_default;

	unsigned int points;
	sf::Text txt_points;
	sf::Text txt_gameover;

	Mapa *map = nullptr;
	Pacman *pacman = nullptr;
	sf::Sprite *life = nullptr;
	std::vector<Ghost> ghosts;

	/*Game functions*/
	GAME_STATES state;
	unsigned int frame_time = 0;

	void game_running();
	void lose_life();
	void game_over();
public:
	Game(sf::RenderWindow &win);
	~Game();

	void handleEvents();
	void update();
	void draw();
};
#endif