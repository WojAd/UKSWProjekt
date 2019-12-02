#include "mapa.h"

Mapa::Mapa(sf::Texture &_tiles_tex)
{
	if (!importMap("resources/map.txt"))
		fillMap(CORRIDOR);
	else
		std::cout << "True\n";
	
	_tile.setTexture(_tiles_tex);
	_tile.setTextureRect(sf::IntRect(sf::Vector2i(0,0),sf::Vector2i(TILE_WIDTH,TILE_HEIGHT)));
	_tile.setOrigin(sf::Vector2f(TILE_WIDTH / 2, TILE_HEIGHT / 2));
}

Mapa::~Mapa()
{
}

void Mapa::draw(sf::RenderWindow &win)
{
	//Centering tiles
	offset = (win.getView().getSize().x - MAP_WIDTH * TILE_WIDTH) / 2;

	//Drawing tiles
	for (unsigned int i = 0; i < MAP_HEIGHT; i++)
	{
		for (unsigned int j = 0; j < MAP_WIDTH; j++)
		{
			if (_map[j][i] == WALL)
			{
				_tile.setPosition(sf::Vector2f(offset + (float)j * TILE_WIDTH + _tile.getOrigin().x, (float)i * TILE_HEIGHT + _tile.getOrigin().y));
				win.draw(_tile);
			}
			else if (_map[j][i] == CORRIDOR)
			{
				continue;
			}
			else
			{
				_map[j][i] = CORRIDOR;
				std::cout << "WARNING: Undefined tile symbol on " << j << ", " << i << "!\n";
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

bool Mapa::importMap(const char *path)
{
	std::ifstream file;
	file.open(path, std::ios_base::in);
	if (!file.good())
		return false;

	char copy_map[MAP_WIDTH][MAP_HEIGHT] = { 0 };
	for (int i=0;!file.eof() && i < MAP_HEIGHT;i++)
	{
		std::string line;
		file >> line;

		if (line.length() < MAP_WIDTH)
		{
			file.close();
			return false;
		}
		else
		{
			for (int j = 0; j < MAP_WIDTH; j++)
			{
				copy_map[j][i] = line[j];
			}
		}
		if (file.eof() && i + 1 < MAP_HEIGHT)
		{
			file.close();
			return false;
		}
	}
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (copy_map[j][i] == CORRIDOR || copy_map[j][i] == WALL)
				this->_map[j][i] = copy_map[j][i];
			else
				this->_map[j][i] = CORRIDOR;
		}
	}

	file.close();
	return true;
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

sf::Vector2f Mapa::tilecoordsToPixels(unsigned int x, unsigned int y)
{
	return sf::Vector2f(offset + (float)x * TILE_WIDTH + _tile.getOrigin().x, (float)y * TILE_HEIGHT + _tile.getOrigin().y);
}

sf::Vector2u Mapa::pixelsToTilecoords(const sf::Vector2f &coords)
{
	sf::Vector2u tile_coords;
	tile_coords.x = (coords.x - this->offset) / TILE_WIDTH;
	tile_coords.y = (coords.y) / TILE_HEIGHT;

	return tile_coords;
}