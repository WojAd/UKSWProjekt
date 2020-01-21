#ifndef GAME_H
#define GAME_H

/** \file Game.h
 * Plik naglowkowy dla klasy gry. Jest to ca³y silnik gry.
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
 * Klasa reprezentuj¹ca ca³y silnik gry
 * @author Rafa³ Œwi¹der
 */
class Game
{
	/**
	* Typ wyliczeniowy reprezentuj¹cy stan gry w jakim siê ona znajduje.
	* @author Rafa³ Œwi¹der
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
	sf::RenderWindow *win = nullptr;/**< WskaŸnik do okna programu*/
	bool _paused;/**< Flaga definiuj¹ca czy gra jest zapauzowana*/
	sf::Uint32 char_entered;/**< Znak wpisany z klawiatury*/

	//Textures
	sf::Texture tex_tiles;/**< Tekstura kafelków mapy*/
	sf::Texture tex_ghost;/**< Tekstura dla duchów*/
	sf::Texture tex_life;/**< Tekstura dla ikony pozosta³ych szans gracza*/
	sf::Texture tex_coin;/**< Tekstura dla monet*/

	//Fonts
	sf::Font fnt_default;/**< Domyœlna czcionka dla tekstów*/

	unsigned int points;/**< Iloœæ zebranych punktów*/
	sf::Text txt_points;/**< Tekst wyœwietlaj¹cy iloœæ punktów*/
	sf::Text txt_gameover;/**< Tekst wyœwietlaj¹cy napis o koñcu gry*/

	sf::RectangleShape pause_background;/**< T³o pauzy w kszta³cie czworok¹ta*/
	sf::Text txt_pause;/**< Tekst informacyjnmy o pauzie*/
	qiwi::Button *button_continue = nullptr;/**< Przycisk kontynuacji po aktywowaniu pauzy*/
	qiwi::Button *button_backtomenu = nullptr;/**< Przycisk powrotu do menu po aktywowaniu pauzy*/
	qiwi::Button *button_exit = nullptr;/**< Przycisk wyjœcia z programu po aktywowaniu pauzy*/

	Mapa *map = nullptr;/**< Mapa gry*/
	Pacman *pacman = nullptr;/**< Pacman kontrolowany przez gracza*/
	sf::Sprite *life = nullptr;/**< Kszta³t szans gracza do wyrysowania*/
	sf::Sprite *coin = nullptr;/**< Kszta³t monet do wyrysowania*/
	std::vector<Ghost> ghosts;/**< Duchy - przeciwnicy pacmana*/



	GAME_STATES state;/**< Stan gry - obecna sytuacja*/
	unsigned int frame_time = 0;/**< Licznik up³yniêtych klatek dla stanów*/

	/**
	* Mechanika rozgrywki
	* @author Rafa³ Œwi¹der
	*/
	void game_running();
	/**
	* Mechanika ma³ej pora¿ki
	* @author Rafa³ Œwi¹der
	*/
	void lose_life();
	/**
	* Mechanika przegrania rozgrywki
	* @author Rafa³ Œwi¹der
	*/
	void game_over();
	/**
	* Mechanika wygranej rozgrywki
	* @author Rafa³ Œwi¹der
	*/
	void game_win();

	/**
	* Metoda wyrysowania monet
	* @author Rafa³ Œwi¹der
	*/
	void draw_coins();
	/**
	* Metoda wyrysowania pozosta³ych szans gracza
	* @author Rafa³ Œwi¹der
	*/
	void draw_lives();

	/**
	* Mechanika obs³ugi pauzy
	* @author Rafa³ Œwi¹der
	*/
	void pause_update();
	/**
	* Metoda wyrysowania pauzy
	* @author Rafa³ Œwi¹der
	*/
	void draw_pause();
public:
	/**
	* Konstruktor klasy silnika gry
	* @param win - Okno programu
	* @author Rafa³ Œwi¹der
	*/
	Game(sf::RenderWindow &win);
	/**
	* Destruktor klasy silnika gry
	* @author Rafa³ Œwi¹der
	*/
	~Game();

	/**
	* Mechanika obs³ugi wydarzeñ(wejœcia z klawiatury, myszki, itp.)
	* @author Rafa³ Œwi¹der
	*/
	void handleEvents();
	/**
	* Ca³a mechanika gry
	* @author Rafa³ Œwi¹der
	*/
	void update();
	/**
	* Metoda wyrysowuj¹ca wszystkie obiekty gry
	* @author Rafa³ Œwi¹der
	*/
	void draw();

	bool go_to_menu = false;/**< Flaga z informacj¹ o przejœciu do menu*/
	/**
	* Metoda resetuj¹ca rozgrywkê
	* @author Rafa³ Œwi¹der
	*/
	void reset_game();
};
#endif