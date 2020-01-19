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

 ///Klasa implementuje posta� Pacmana wy�wietlan� na ekranie.
class Pacman : public Drawable {
public:
	/// @param x parametr okre�laj�cy pocz�tkow� pozycj� Pacmana na osi OX
	/// @param y parametr okre�laj�cy pocz�tkow� pozycj� Pacmana na osi OY
	/// @param lives parametr okre�laj�cy pocz�tkow� liczb� �ycia Pacmana
	/// @param windowWidth parametr, w kt�ry powinno si� poda� szeroko�� okna. Pacman nie b�dzie m�g� wyj�� poza okre�lon� szeroko��.
	/// @param windowHeight parametr, w kt�ry powinno si� poda� wysoko�� okna. Pacman nie b�dzie m�g� wyj�� poza okre�lon� wysoko��.
	/// @param map okre�la do jakiej mapy ma by� przyporz�dkowany Pacman
	Pacman(float x, float y, int lives, int windowWidth, int windowHeight, Mapa* map);

	/// Metoda odpowiedzialna za poruszanie si� Pacmana, jego animacj� i kolizj� ze �cianami
	void update();

	/// zmienne przechowuj� warto�ci podane w konstruktorze.
	/// @see Pacman(float, float, int, int, int, Mapa*)
	int windowWidth, windowHeight;

	/// @returns Metoda zwraca obecn� liczb� �ycia Pacmana
	int getLives();

	/// @returns Metoda zwraca pozycj� Pacmana na mapie w postaci zmiennej typu sf::Vector2f
	Vector2f getPosition();

	/// Metoda ustawia Pacmana we wskazanej pozycji na mapie.
	/// @param pos parametr typu sf::Vector2f zawierajacy pozycj�, na kt�rej ma znale�� si� Pacman
	void setPosition(Vector2f &pos);

	/// @returns Metoda zwraca obiekt typu Sprite zawierajacy informacje o Pacmanie np. jego pozycj� i tekstur�.
	Sprite getSprite() const;

	/// Obiekt ustawia �ycie Pacmana na podan� w argumencie warto��.
	/// @param lives Warto�� typu int zawierajaca ilo�� �ycia Pacmana, kt�ra ma by� ustawiona.
	void setLives(int lives);

	/// Metoda zatrzymuje Pacmana w miejscu.
	void killPacman();

	/// Metoda ustawia szybko�� Pacmana na warto�� domy�ln�.
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
