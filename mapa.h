#ifndef MAPA_H
#define MAPA_H

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>

#define MAP_WIDTH 19
#define MAP_HEIGHT 19

#define TILE_WIDTH 40
#define TILE_HEIGHT 40

#define CORRIDOR '.'
#define WALL '#'

class Mapa
{
private:
	char _map[MAP_WIDTH][MAP_HEIGHT];
	sf::Sprite _tile;//For drawing
	float offset = -1;//Offset for centering tiles

	//Tiles order in texture
	const bool t_corridor = 0;
	const bool t_wall = 1;

public:
	Mapa(sf::Texture &_tiles_tex);
	~Mapa();

	void draw(sf::RenderWindow &win);

	void fillMap(char type);
	bool importMap(const char *path);
	void setTile(unsigned int x, unsigned int y, char type);
	char getTile(unsigned int x, unsigned int y);
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