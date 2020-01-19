#ifndef GAME_H
#define GAME_H

#include "FilePaths.h"
#include "mapa.h"
#include "pacman.h"
#include "duch.h"
#include "Button.h"

#define LOSE_LIFE_FRAME_TIME 120

#define PACMAN_START_X 512
#define PACMAN_START_Y 620
//#define PACMAN_MAX_LIVES 3

#define GHOST_AMOUNT 3

#define LIFE_WIDTH 30
#define LIFE_HEIGHT 30
#define LIFE_X 5
#define LIFE_Y 40

#define COIN_WIDTH 10
#define COIN_HEIGHT 10

#define TXT_POINTS_X 5
#define TXT_POINTS_Y 5
#define TXT_POINTS_SIZE 18

#define TXT_GAMEOVER_SIZE 72

#define TXT_PAUSE_Y 250
#define BACKGROUND_PAUSE_WIDTH 300
#define BACKGROUND_PAUSE_HEIGHT 300
#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 30
#define BUTTON_CONTINUE_Y 300
#define BUTTON_BACKTOMENU_Y 350
#define BUTTON_EXIT_Y 400

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
	bool _paused;
	sf::Uint32 char_entered;

	//Textures
	sf::Texture tex_tiles;
	//sf::Texture tex_pacman;
	sf::Texture tex_life;
	sf::Texture tex_coin;

	//Fonts
	sf::Font fnt_default;

	unsigned int points;
	sf::Text txt_points;
	sf::Text txt_gameover;

	sf::RectangleShape pause_background;
	sf::Text txt_pause;
	qiwi::Button *button_continue = nullptr;
	qiwi::Button *button_backtomenu = nullptr;
	qiwi::Button *button_exit = nullptr;

	Mapa *map = nullptr;
	Pacman *pacman = nullptr;
	sf::Sprite *life = nullptr;
	sf::Sprite *coin = nullptr;
	std::vector<Ghost> ghosts;

	/*Game functions*/
	GAME_STATES state;
	unsigned int frame_time = 0;

	void game_running();
	void lose_life();
	void game_over();

	void draw_coins();
	void draw_lives();

	void pause_update();
	void draw_pause();
public:
	Game(sf::RenderWindow &win);
	~Game();

	void handleEvents();
	void update();
	void draw();

	bool go_to_menu = false;
	void reset_game();
};
#endif