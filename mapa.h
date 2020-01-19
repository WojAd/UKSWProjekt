#ifndef MAPA_H
#define MAPA_H

/** \file mapa.h
 * Plik naglowkowy dla klas potrzebnych do obslugi mapy i jej obiekt�w.
 */

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>

#include "FilePaths.h"

#define MAP_WIDTH 19
#define MAP_HEIGHT 19

#define TILE_WIDTH 40
#define TILE_HEIGHT 40

#define CORRIDOR '.'
#define WALL '#'
#define BLANK '-'

 /**
 * Klasa reprezentuj�ca map� gry
 * @author Rafa� �wi�der
 */
class Mapa
{
private:
	char _map[MAP_WIDTH][MAP_HEIGHT];/**< Tablica kafelk�w mapy*/
	bool _coinmap[MAP_WIDTH][MAP_HEIGHT];/**< Tablica istniej�cych monet*/
	sf::Sprite _tile;/**< Sprite dla kafelk�w do wyrysowania w oknie*/
	float offset;/**< Odst�p mapy od lewej strony okna dla wy�rodkowania*/

	short _coinquantity;/**< Ilo�� monet znajduj�cych si� na mapie*/
public:
	/**
	* Konstruktor mapy
	* /param _tiles_tex - tekstura kafelk�w wczytana z pliku
	* @author Rafa� �wi�der
	*/
	Mapa(sf::Texture &_tiles_tex);

	/**
	* Destruktor mapy
	* @author Rafa� �wi�der
	*/
	~Mapa();

	/**
	* Metoda rysuj�ca map� w oknie
	* /param win - okno, w kt�rym ma by� wyrysowana mapa
	* @author Rafa� �wi�der
	*/
	void draw(sf::RenderWindow &win);

	/**
	* Wype�nianie mapy konkretnym kafelkiem
	* /param type - typ kafelka
	* @author Rafa� �wi�der
	*/
	void fillMap(char type);
	/**
	* Importowanie mapy z pliku
	* /param path - �cie�ka do pliku
	* @author Rafa� �wi�der
	*/
	bool importMap(const char *path);
	/**
	* Podmiana kafelka w mapie
	* /param x - Kolumna kafelka do podmiany
	* /param y - Wiersz kafelka do podmiany
	* /param type - Typ kafelka, jaki ma by� wstawiony
	* @author Rafa� �wi�der
	*/
	void setTile(unsigned int x, unsigned int y, char type);
	/**
	* Pobranie typu danego kafelka z mapy
	* /param x - Kolumna kafelka do podmiany
	* /param y - Wiersz kafelka do podmiany
	* @author Rafa� �wi�der
	*/
	char getTile(unsigned int x, unsigned int y);
	/**
	* Ustawianie monet na mapie
	* /param x - Kolumna kafelka
	* /param y - Wiersz kafelka
	* /param coin - Decyzja o istnieniu monety na danym kafelku
	* @author Rafa� �wi�der
	*/
	void setCoinTile(unsigned int x, unsigned int y, bool coin);
	/**
	* Pobranie informacji o istniej�cej monecie na danym kafelku mapy
	* /param x - Kolumna kafelka do podmiany
	* /param y - Wiersz kafelka do podmiany
	* @author Rafa� �wi�der
	*/
	bool getCoinTile(unsigned int x, unsigned int y);
	/**
	* Pobranie ilo�ci monet na mapie
	* @author Rafa� �wi�der
	*/
	short getCoinQuantity();

	/**
	* Konwersja z pozycji kafelka w tablicy na piksele
	* /param x - Kolumna kafelka
	* /param y - Wiersz kafelka
	* @return Zwraca koordynaty kafelka w oknie w pikselach
	* @author Rafa� �wi�der
	*/
	sf::Vector2f tilecoordsToPixels(unsigned int x, unsigned int y);
	/**
	* Konwersja z pozycji piksela na kafelek w tablicy
	* /param coords - Wektor 2D zawieraj�cy pozycj� piksela
	* @return Zwraca koordynaty kafelka, do kt�rego nale�y piksel
	* @author Rafa� �wi�der
	*/
	sf::Vector2u pixelsToTilecoords(const sf::Vector2f &coords);
	/**
	* Pobranie odst�pu mapy od lewej strony okna
	* @return Zwraca przesuni�cie mapy od lewej strony okna w pikselach
	* @author Rafa� �wi�der
	*/
	float getOffset();
};
#endif

/////////////////////////////////////////////////////////
//////////////////////TILES TYPES////////////////////////
/////////////////////////////////////////////////////////
//
// '.' - corridor
// '#' - wall
// '-' - void
//
/////////////////////////////////////////////////////////