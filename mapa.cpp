#include "mapa.h"

Mapa::Mapa(sf::Texture &_tiles_tex)
{
	fillMap(' ');//For now...
	_tile.setTexture(_tiles_tex);
}

Mapa::~Mapa()
{
}

void Mapa::draw(sf::RenderWindow &win)
{
	for (unsigned int i = 0; i < MAP_HEIGHT; i++)
	{
		for (unsigned int j = 0; j < MAP_WIDTH; j++)
		{
			switch (_map[j][i])
			{
			case '+':
				_tile.setTextureRect(sf::IntRect(t_cross*TILE_WIDTH, 0, TILE_WIDTH, TILE_HEIGHT));
				break;
			case '|':
				_tile.setTextureRect(sf::IntRect(t_vertical*TILE_WIDTH, 0, TILE_WIDTH, TILE_HEIGHT));
				break;
			case '-':
				_tile.setTextureRect(sf::IntRect(t_horizontal*TILE_WIDTH, 0, TILE_WIDTH, TILE_HEIGHT));
				break;
			case '<':
				_tile.setTextureRect(sf::IntRect(t_left*TILE_WIDTH, 0, TILE_WIDTH, TILE_HEIGHT));
				break;
			case '>':
				_tile.setTextureRect(sf::IntRect(t_right*TILE_WIDTH, 0, TILE_WIDTH, TILE_HEIGHT));
				break;
			case '^':
				_tile.setTextureRect(sf::IntRect(t_up*TILE_WIDTH, 0, TILE_WIDTH, TILE_HEIGHT));
				break;
			case 'V':
				_tile.setTextureRect(sf::IntRect(t_down*TILE_WIDTH, 0, TILE_WIDTH, TILE_HEIGHT));
				break;
			default:
				_tile.setTextureRect(sf::IntRect(t_corridor*TILE_WIDTH, 0, TILE_WIDTH, TILE_HEIGHT));
				break;
			}
		}
	}
}

void Mapa::fillMap(char type)
{
	for (unsigned int i = 0; i < MAP_HEIGHT; i++)
	{
		for (unsigned int j = 0; j < MAP_WIDTH; j++)
		{
			this->_map[j][i] = type;
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