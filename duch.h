#ifndef GHOST_H
#define GHOST_H

using namespace std;

#include <SFML/Graphics.hpp>
#include <thread>
#include <deque>

#define sizeMapX 20
#define sizeMapY 20

class Node {
public:
	short X;
	short Y;
	Node* parent;

	Node() { X = 0; Y = 0; parent = NULL; }
	Node(short X, short Y) { this->X = X; this->Y = Y; parent = NULL; }
	~Node() {};

	bool isNeighbour(Node param) { if (param.X >= X - 1 || X >= param.X - 1 || param.Y >= Y - 1 || Y >= param.Y - 1) return true; else return false; }
	short distance(Node param) { return sqrt(pow(abs(param.X - X), 2) + pow(abs(param.Y - Y), 2)); }
};

class Ghost {
	char* pacmanX;
	char* pacmanY;
	char map[sizeMapX][sizeMapY];
	std::deque<Node> deWay;

	void si();
	
public:
	sf::Sprite sprite;

	Ghost(char* pacmanX, char* pacmanY, char map[sizeMapY][sizeMapX]);
	~Ghost();
};

#endif //GHOST_H