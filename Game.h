#ifndef GAME_H
#define GAME_H

/** \file Game.h
 * Plik naglowkowy dla klasy gry. Jest to ca�y silnik gry.
 */


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


/**
 * Klasa reprezentuj�ca ca�y silnik gry
 * @author Rafa� �wi�der
 */
class Game
{
	/**
	* Typ wyliczeniowy reprezentuj�cy stan gry w jakim si� ona znajduje.
	* @author Rafa� �wi�der
	*/
	enum GAME_STATES
	{
		READY,
		RUNNING,
		LOSE_LIFE,
		GAME_OVER,
		GAME_WON
	};

private:
	sf::RenderWindow *win = nullptr;/**< Wska�nik do okna programu*/
	bool _paused;/**< Flaga definiuj�ca czy gra jest zapauzowana*/
	sf::Uint32 char_entered;/**< Znak wpisany z klawiatury*/

	//Textures
	sf::Texture tex_tiles;/**< Tekstura kafelk�w mapy*/
	sf::Texture tex_ghost;/**< Tekstura dla duch�w*/
	sf::Texture tex_life;/**< Tekstura dla ikony pozosta�ych szans gracza*/
	sf::Texture tex_coin;/**< Tekstura dla monet*/

	//Fonts
	sf::Font fnt_default;/**< Domy�lna czcionka dla tekst�w*/

	unsigned int points;/**< Ilo�� zebranych punkt�w*/
	sf::Text txt_points;/**< Tekst wy�wietlaj�cy ilo�� punkt�w*/
	sf::Text txt_gameover;/**< Tekst wy�wietlaj�cy napis o ko�cu gry*/

	sf::RectangleShape pause_background;/**< T�o pauzy w kszta�cie czworok�ta*/
	sf::Text txt_pause;/**< Tekst informacyjnmy o pauzie*/
	qiwi::Button *button_continue = nullptr;/**< Przycisk kontynuacji po aktywowaniu pauzy*/
	qiwi::Button *button_backtomenu = nullptr;/**< Przycisk powrotu do menu po aktywowaniu pauzy*/
	qiwi::Button *button_exit = nullptr;/**< Przycisk wyj�cia z programu po aktywowaniu pauzy*/

	Mapa *map = nullptr;/**< Mapa gry*/
	Pacman *pacman = nullptr;/**< Pacman kontrolowany przez gracza*/
	sf::Sprite *life = nullptr;/**< Kszta�t szans gracza do wyrysowania*/
	sf::Sprite *coin = nullptr;/**< Kszta�t monet do wyrysowania*/
	std::vector<Ghost> ghosts;/**< Duchy - przeciwnicy pacmana*/



	GAME_STATES state;/**< Stan gry - obecna sytuacja*/
	unsigned int frame_time = 0;/**< Licznik up�yni�tych klatek dla stan�w*/

	/**
	* Mechanika rozgrywki
	* @author Rafa� �wi�der
	*/
	void game_running();
	/**
	* Mechanika ma�ej pora�ki
	* @author Rafa� �wi�der
	*/
	void lose_life();
	/**
	* Mechanika przegrania rozgrywki
	* @author Rafa� �wi�der
	*/
	void game_over();
	/**
	* Mechanika wygranej rozgrywki
	* @author Rafa� �wi�der
	*/
	void game_win();

	/**
	* Metoda wyrysowania monet
	* @author Rafa� �wi�der
	*/
	void draw_coins();
	/**
	* Metoda wyrysowania pozosta�ych szans gracza
	* @author Rafa� �wi�der
	*/
	void draw_lives();

	/**
	* Mechanika obs�ugi pauzy
	* @author Rafa� �wi�der
	*/
	void pause_update();
	/**
	* Metoda wyrysowania pauzy
	* @author Rafa� �wi�der
	*/
	void draw_pause();
public:
	/**
	* Konstruktor klasy silnika gry
	* @param win - Okno programu
	* @author Rafa� �wi�der
	*/
	Game(sf::RenderWindow &win);
	/**
	* Destruktor klasy silnika gry
	* @author Rafa� �wi�der
	*/
	~Game();

	/**
	* Mechanika obs�ugi wydarze�(wej�cia z klawiatury, myszki, itp.)
	* @author Rafa� �wi�der
	*/
	void handleEvents();
	/**
	* Ca�a mechanika gry
	* @author Rafa� �wi�der
	*/
	void update();
	/**
	* Metoda wyrysowuj�ca wszystkie obiekty gry
	* @author Rafa� �wi�der
	*/
	void draw();

	bool go_to_menu = false;/**< Flaga z informacj� o przej�ciu do menu*/
	/**
	* Metoda resetuj�ca rozgrywk�
	* @author Rafa� �wi�der
	*/
	void reset_game();
};
#endif