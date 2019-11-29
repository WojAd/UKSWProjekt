#include "mapa.h"

Mapa::Mapa(sf::Texture &_tiles_tex)
{
	if (!importMap("resources/map.txt"))
		fillMap(' ');
	else
		std::cout << "True\n";
	
	_tile.setTexture(_tiles_tex);
	_tile.setTextureRect(sf::IntRect(sf::Vector2i(0,0),sf::Vector2i(TILE_WIDTH,TILE_HEIGHT)));

}

Mapa::~Mapa()
{
}

void Mapa::draw(sf::RenderWindow &win)
{
	//Centering tiles
	if (offset == -1)
		offset = (win.getView().getSize().x - MAP_WIDTH * TILE_WIDTH) / 2;

	//Drawing tiles
	for (unsigned int i = 0; i < MAP_HEIGHT; i++)
	{
		for (unsigned int j = 0; j < MAP_WIDTH; j++)
		{
			if (_map[j][i] == '#')
			{
				_tile.setPosition(sf::Vector2f(offset + j*TILE_WIDTH, i*TILE_HEIGHT));
				win.draw(_tile);
			}
			else if (_map[j][i] == ' ')
				continue;
			else
				std::cout << "WARNING: Undefined tile symbol!\n";
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
			if (copy_map[j][i] == ' ' || copy_map[j][i] == '#')
				this->_map[j][i] = copy_map[j][i];
			else
				this->_map[j][i] = ' ';
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