#ifndef GHOST_H
#define GHOST_H

using namespace std;

#include <SFML/Graphics.hpp>
/** \file duch.h
 * Plik naglowkowy dla klas potrzebnych do obslugi duszkow.
 * Znajduja sie tu definicje klasy punktow (dla algorytmu A*), oraz klasy ducha.
 */

#include <deque>
#include <iostream>
#include <thread>
#include <algorithm>
#include "mapa.h"
#include <vector>
using namespace std;
using namespace sf;

#define sizeMapX 20
#define sizeMapY 20
#define IMG_WIDTH 40
#define IMG_HEIGHT 40

/**
* Klasa reprezentujaca dwu-wymiarowy punkt
* @author Adrian Wojciechowski
*/
class Node {
public:
	/*@{*/
	short X; /**< Koordynat X */
	short Y; /**< Koordynat Y */
	Node* parent; /**< Rodzic punktu (dla algorytmu A*) */
	double dCost; /**< Sumaryczny koszt drogi do najstarszego przodka */
	 /*@}*/

	/**
	* Konstruktor domyslny punktu
	* @author Adrian Wojciechowski
	*/
	Node() { X = 0; Y = 0; parent = NULL; dCost = 0; }
	/**
	* Konstruktor z inicjalizacja punktu
	* /param X
	* /param Y
	* @author Adrian Wojciechowski
	*/
	Node(short X, short Y) { this->X = X; this->Y = Y; parent = NULL; dCost = 0; }
	/**
	* Konstruktor z inicjalizacja punktu i rodzica
	* /param X
	* /param Y
	* /param param
	* @author Adrian Wojciechowski
	*/
	Node(short X, short Y, Node* param) { this->X = X; this->Y = Y; parent = param; dCost = 0; }
	/**
	* Konstruktor kopiujacy
	* /param param
	* @author Adrian Wojciechowski
	*/
	Node(const Node& param) { X = param.X; Y = param.Y; parent = param.parent; dCost = param.dCost; }
	/**
	* Konstruktor z inicjalizacja punktu, kosztu i rodzica
	* /param X
	* /param Y
	* /param dCost
	* /param param
	* @author Adrian Wojciechowski
	*/
	Node(short X, short Y, short dCost, Node* param) { this->X = X; this->Y = Y; parent = param; this->dCost = dCost; }
	/**
	* Destruktor
	* @author Adrian Wojciechowski
	*/
	~Node() {};

	/**
	* Metoda sprawdza, czy punkt jest s¹siadem innego punktu
	* /param param
	* @author Adrian Wojciechowski
	* @return bool - czy punkt jest sasiadem
	*/
	bool isNeighbour(Node param) { if (((param.X == X - 1 || X == param.X - 1) && param.Y == Y) || (param.X == X && (param.Y == Y - 1 || Y == param.Y - 1))) return true; else return false; }
	/**
	* Metoda oblicza odleglosc miedzy punktami ze wzoru pitagorasa
	* /param param
	* @author Adrian Wojciechowski
	* @return double - odleglosc
	*/
	double getDistance(Node param) { return sqrt(pow(abs(param.X - X), 2) + pow(abs(param.Y - Y), 2)); }
	/**
	* Metoda sprawdza, czy punktu znajduja sie w innym miejscu
	* /param param
	* @author Adrian Wojciechowski
	* @return bool - zwraca prawde, gdy X, Y sa rozne
	*/
	bool operator!=(const Node& param) const { return (X != param.X || Y != param.Y); }
	/**
	* Metoda sprawdza, czy punkty znajduja sie w tym samym miejscu
	* /param param
	* @author Adrian Wojciechowski
	* @return bool - zwraca prawde, gdy X, Y sa takie same
	*/
	bool operator==(const Node& param) const { return (X == param.X && Y == param.Y); }
};

/**
* Klasa reprezentuj¹ca duszka
* @author Adrian Wojciechowski
*/
class Ghost : public Drawable {
	/*@{*/
	short destX; /**< Koordynat X */
	short destY; /**< Koordynat Y */
	deque<Node> map; /**< Lista punktow po ktorych moze poruszac sie duszek */
	std::vector<Node> deWay; /**< Sciezka z zaplanowana trasa duszka */
	std::vector<Node> newDeWay; /**< Tymczasowa sciezka z zaplanowana trasa duszka, do przekopiowania i poprawienia po zakonczeniu dzialania algorytmu A* */
	Sprite sprite; /**< Sprite duszka */
	Texture texture; /**< Tekstura duszka */
	const float ghostVelocity{ 4.0f }; /**< Maksymalna predkosc duszka */
	Vector2f velocity{ 0.0f,0.0f }; /**< Wektor ruchu duszka */
	Mapa* mapPointer; /**< Wskaznik na obiekt mapy */
	thread* threads; /**< Aktywny watek dla algorytmu A* */
	bool threading; /**< Informacja o zakonczeniu dzialania watku */
	/*@}*/

	/**
	* Funkcja realizujaca algorytm A*
	* Algorytm przeszukuje punkty po ktorych moze poruszac sie duszek od punktu w ktorym znajduje sie duszek do punktu docelowego.
	* Algorytm przeznaczony do uruchamiania w watku
	* @author Adrian Wojciechowski
	*/
	void si();

public:
	/**
	* Geter dla koordynatu X duszka
	* @author Adrian Wojciechowski
	* @return double - Koordynat X duszka
	*/
	double getX() { return sprite.getPosition().x; }
	/**
	* Geter dla koordynatu Y duszka
	* @author Adrian Wojciechowski
	* @return double - Koordynat Y duszka
	*/
	double getY() { return sprite.getPosition().y; }
	/**
	* Geter dla koordynatow duszka
	* @author Adrian Wojciechowski
	* @return Vector2f - koordynaty duszka
	*/
	sf::Vector2f getPosition() { return sprite.getPosition(); }
	/**
	* Metoda zmieniajaca punkt w ktorym znajduje sie duszek.
	* Dodatkowo czyszczona jest zaplanowana trasa duszka.
	* /param param
	* @author Adrian Wojciechowski
	*/
	void setPosition(sf::Vector2f param) { sprite.setPosition(param); deWay.clear(); }

	/**
	* Konstruktor z inicjalizacja punktu w ktorym znajduje sie duszek
	* /param x
	* /param y
	* /param map
	* @author Adrian Wojciechowski
	*/
	Ghost(int x, int y, Mapa* map, sf::Texture &texture);
	/**
	* Destruktor
	* @author Adrian Wojciechowski
	*/
	~Ghost();

	/**
	* Metoda implementujaca sposob dzialania duszka w kazdej klatce animacji
	* /param destXParam
	* /param destYParam
	* @author Adrian Wojciechowski
	*/
	void update(float destXParam, float destYParam);
	/**
	* Metoda rysujaca duszka na ekranie
	* /param target
	* /param state
	* @author Adrian Wojciechowski
	*/
	void draw(RenderTarget& target, RenderStates state) const override;
	/**
	* Metoda pozwala pobrac Sprite duszka
	* @author Adrian Wojciechowski
	* @return Sprite
	*/
	Sprite getSprite() const;
};

#endif //GHOST_H