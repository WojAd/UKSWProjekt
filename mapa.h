#ifndef MAPA_H
#define MAPA_H

#include <SFML/Graphics.hpp>

#define MAP_WIDTH 20
#define MAP_HEIGHT 20

#define TILE_WIDTH 50
#define TILE_HEIGHT 50

class Mapa
{
private:
	char _map[MAP_WIDTH][MAP_HEIGHT];
	sf::Sprite _tile;//For drawing

	//Tiles order in texture
	const int t_corridor = 0;
	const int t_cross = 1;
	const int t_vertical = 2;
	const int t_horizontal = 3;
	const int t_left = 4;
	const int t_right = 5;
	const int t_up = 6;
	const int t_down = 7;

public:
	Mapa(sf::Texture &_tiles_tex);
	~Mapa();

	void draw(sf::RenderWindow &win);

	void fillMap(char type);
	void setTile(unsigned int x, unsigned int y, char type);
	char getTile(unsigned int x, unsigned int y);
};
#endif

/////////////////////////////////////////////////////////
//////////////////////TILES TYPES////////////////////////
/////////////////////////////////////////////////////////
//
// ' ' - empty space
// '#' - wall
//
/////////////////////////////////////////////////////////