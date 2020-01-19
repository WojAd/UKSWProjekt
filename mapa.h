#ifndef MAPA_H
#define MAPA_H

/** \file mapa.h
 * Plik naglowkowy dla klas potrzebnych do obslugi mapy i jej obiektów.
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
 * Klasa reprezentuj¹ca mapê gry
 * @author Rafa³ Œwi¹der
 */
class Mapa
{
private:
	char _map[MAP_WIDTH][MAP_HEIGHT];/**< Tablica kafelków mapy*/
	bool _coinmap[MAP_WIDTH][MAP_HEIGHT];/**< Tablica istniej¹cych monet*/
	sf::Sprite _tile;/**< Sprite dla kafelków do wyrysowania w oknie*/
	float offset;/**< Odstêp mapy od lewej strony okna dla wyœrodkowania*/

	short _coinquantity;/**< Iloœæ monet znajduj¹cych siê na mapie*/
public:
	/**
	* Konstruktor mapy
	* /param _tiles_tex - tekstura kafelków wczytana z pliku
	* @author Rafa³ Œwi¹der
	*/
	Mapa(sf::Texture &_tiles_tex);

	/**
	* Destruktor mapy
	* @author Rafa³ Œwi¹der
	*/
	~Mapa();

	/**
	* Metoda rysuj¹ca mapê w oknie
	* /param win - okno, w którym ma byæ wyrysowana mapa
	* @author Rafa³ Œwi¹der
	*/
	void draw(sf::RenderWindow &win);

	/**
	* Wype³nianie mapy konkretnym kafelkiem
	* /param type - typ kafelka
	* @author Rafa³ Œwi¹der
	*/
	void fillMap(char type);
	/**
	* Importowanie mapy z pliku
	* /param path - œcie¿ka do pliku
	* @author Rafa³ Œwi¹der
	*/
	bool importMap(const char *path);
	/**
	* Podmiana kafelka w mapie
	* /param x - Kolumna kafelka do podmiany
	* /param y - Wiersz kafelka do podmiany
	* /param type - Typ kafelka, jaki ma byæ wstawiony
	* @author Rafa³ Œwi¹der
	*/
	void setTile(unsigned int x, unsigned int y, char type);
	/**
	* Pobranie typu danego kafelka z mapy
	* /param x - Kolumna kafelka do podmiany
	* /param y - Wiersz kafelka do podmiany
	* @author Rafa³ Œwi¹der
	*/
	char getTile(unsigned int x, unsigned int y);
	/**
	* Ustawianie monet na mapie
	* /param x - Kolumna kafelka
	* /param y - Wiersz kafelka
	* /param coin - Decyzja o istnieniu monety na danym kafelku
	* @author Rafa³ Œwi¹der
	*/
	void setCoinTile(unsigned int x, unsigned int y, bool coin);
	/**
	* Pobranie informacji o istniej¹cej monecie na danym kafelku mapy
	* /param x - Kolumna kafelka do podmiany
	* /param y - Wiersz kafelka do podmiany
	* @author Rafa³ Œwi¹der
	*/
	bool getCoinTile(unsigned int x, unsigned int y);
	/**
	* Pobranie iloœci monet na mapie
	* @author Rafa³ Œwi¹der
	*/
	short getCoinQuantity();

	/**
	* Konwersja z pozycji kafelka w tablicy na piksele
	* /param x - Kolumna kafelka
	* /param y - Wiersz kafelka
	* @return Zwraca koordynaty kafelka w oknie w pikselach
	* @author Rafa³ Œwi¹der
	*/
	sf::Vector2f tilecoordsToPixels(unsigned int x, unsigned int y);
	/**
	* Konwersja z pozycji piksela na kafelek w tablicy
	* /param coords - Wektor 2D zawieraj¹cy pozycjê piksela
	* @return Zwraca koordynaty kafelka, do którego nale¿y piksel
	* @author Rafa³ Œwi¹der
	*/
	sf::Vector2u pixelsToTilecoords(const sf::Vector2f &coords);
	/**
	* Pobranie odstêpu mapy od lewej strony okna
	* @return Zwraca przesuniêcie mapy od lewej strony okna w pikselach
	* @author Rafa³ Œwi¹der
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