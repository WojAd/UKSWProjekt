#ifndef PACMAN_H
#define PACMAN_H

//#include <SFML/Graphics.hpp>
#include "mapa.h"
#include "FilePaths.h"
#include"SFML/Graphics.hpp"


//#define IMG_WIDTH 53
//#define IMG_HEIGHT 58

#define FRAME_WIDTH 40
#define FRAME_HEIGHT 40
#define IMG_WIDTH 200
#define IMG_HEIGHT 160
#define PACMAN_MAX_LIVES 3

using namespace std;
using namespace sf;

 ///Klasa implementuje postaæ Pacmana wyœwietlan¹ na ekranie.
class Pacman : public Drawable {
public:
	/// @param x parametr okreœlaj¹cy pocz¹tkow¹ pozycjê Pacmana na osi OX
	/// @param y parametr okreœlaj¹cy pocz¹tkow¹ pozycjê Pacmana na osi OY
	/// @param lives parametr okreœlaj¹cy pocz¹tkow¹ liczbê ¿ycia Pacmana
	/// @param windowWidth parametr, w który powinno siê podaæ szerokoœæ okna. Pacman nie bêdzie móg³ wyjœæ poza okreœlon¹ szerokoœæ.
	/// @param windowHeight parametr, w który powinno siê podaæ wysokoœæ okna. Pacman nie bêdzie móg³ wyjœæ poza okreœlon¹ wysokoœæ.
	/// @param map okreœla do jakiej mapy ma byæ przyporz¹dkowany Pacman
	Pacman(float x, float y, int lives, int windowWidth, int windowHeight, Mapa* map);

	/// Metoda odpowiedzialna za poruszanie siê Pacmana, jego animacjê i kolizjê ze œcianami
	void update();

	/// zmienne przechowuj¹ wartoœci podane w konstruktorze.
	/// @see Pacman(float, float, int, int, int, Mapa*)
	int windowWidth, windowHeight;

	/// @returns Metoda zwraca obecn¹ liczbê ¿ycia Pacmana
	int getLives();

	/// @returns Metoda zwraca pozycjê Pacmana na mapie w postaci zmiennej typu sf::Vector2f
	Vector2f getPosition();

	/// Metoda ustawia Pacmana we wskazanej pozycji na mapie.
	/// @param pos parametr typu sf::Vector2f zawierajacy pozycjê, na której ma znaleŸæ siê Pacman
	void setPosition(Vector2f &pos);

	/// @returns Metoda zwraca obiekt typu Sprite zawierajacy informacje o Pacmanie np. jego pozycjê i teksturê.
	Sprite getSprite() const;

	/// Obiekt ustawia ¿ycie Pacmana na podan¹ w argumencie wartoœæ.
	/// @param lives Wartoœæ typu int zawierajaca iloœæ ¿ycia Pacmana, która ma byæ ustawiona.
	void setLives(int lives);

	/// Metoda zatrzymuje Pacmana w miejscu.
	void killPacman();

	/// Metoda ustawia szybkoœæ Pacmana na wartoœæ domyœln¹.
	void revivePacman();
private:
	Clock clock;
	IntRect textRect;
	int changeFrameStep;
	Texture texture;
	Sprite sprite;
	int lives;
	float pacVelocity{ 4.1f };
	Vector2f velocity{ 0.0f,0.0f };
	void draw(RenderTarget& target, RenderStates state) const override;
	float left();
	float right();
	float top();
	float bottom();
	Mapa *map;
};

#endif
