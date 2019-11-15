#ifndef MAPA_H
#define MAPA_H

#include <SFML/Graphics.hpp>

#define MAP_WIDTH 20
#define MAP_HEIGHT 20

#define TILE_WIDTH 50
#define TILE_HEIGHT 50

class Mapa : public sf::Drawable
{
private:
	char _map[MAP_WIDTH][MAP_HEIGHT];
	sf::Sprite _tile;//For drawing

public:
	Mapa();
	~Mapa();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

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