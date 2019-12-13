#ifndef MAPA_H
#define MAPA_H

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

class Mapa
{
private:
	char _map[MAP_WIDTH][MAP_HEIGHT];
	bool _coinmap[MAP_WIDTH][MAP_HEIGHT];
	sf::Sprite _tile;//For drawing
	float offset;//Offset for centering tiles

public:
	Mapa(sf::Texture &_tiles_tex);
	~Mapa();

	void draw(sf::RenderWindow &win);

	void fillMap(char type);
	bool importMap(const char *path);
	void setTile(unsigned int x, unsigned int y, char type);
	char getTile(unsigned int x, unsigned int y);
	void setCoinTile(unsigned int x, unsigned int y, bool coin);
	bool getCoinTile(unsigned int x, unsigned int y);

	sf::Vector2f tilecoordsToPixels(unsigned int x, unsigned int y);//Returns centre of tile
	sf::Vector2u pixelsToTilecoords(const sf::Vector2f &coords);
	float getOffset();
};
#endif

/////////////////////////////////////////////////////////
//////////////////////TILES TYPES////////////////////////
/////////////////////////////////////////////////////////
//
// '.' - empty space
// '#' - wall
//
/////////////////////////////////////////////////////////