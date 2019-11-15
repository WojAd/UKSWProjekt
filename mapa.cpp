#include "mapa.h"

Mapa::Mapa()
{
	fillMap(' ');//For now...
}

Mapa::~Mapa()
{

}

void Mapa::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//...
}

void Mapa::fillMap(char type)
{
	for (unsigned int i = 0; i < MAP_HEIGHT; i++)
	{
		for (unsigned int j = 0; j < MAP_WIDTH; j++)
		{
			_map[j][i] = type;
		}
	}
}

void Mapa::setTile(unsigned int x, unsigned int y, char type)
{
	if (x < 0)
		x = 0;
	else if (x >= MAP_WIDTH)
		x = MAP_WIDTH - 1;

	if (y < 0)
		y = 0;
	else if (y >= MAP_HEIGHT)
		y = MAP_HEIGHT - 1;

	_map[x][y] = type;
}

char Mapa::getTile(unsigned int x, unsigned int y)
{
	if (x < 0)
		x = 0;
	else if (x >= MAP_WIDTH)
		x = MAP_WIDTH - 1;

	if (y < 0)
		y = 0;
	else if (y >= MAP_HEIGHT)
		y = MAP_HEIGHT - 1;

	return _map[x][y];
}