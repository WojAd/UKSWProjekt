#ifndef GHOST_H
#define GHOST_H

using namespace std;

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <thread>
#include <deque>
#include <iostream>
#include "mapa.h"
using namespace std;
using namespace sf;

#define sizeMapX 20
#define sizeMapY 20
#define IMG_WIDTH 40
#define IMG_HEIGHT 40

enum {north, south, west, east};

class Node {
public:
	short X;
	short Y;
	Node* parent;

	Node() { X = 0; Y = 0; parent = NULL; }
	Node(short X, short Y) { this->X = X; this->Y = Y; parent = NULL; }
	Node(short X, short Y, Node* param) { this->X = X; this->Y = Y; parent = param; }
	Node(const Node& param) { X = param.X; Y = param.Y; parent = param.parent; }
	~Node() {};

	bool isNeighbour(Node param) { if (param.X >= X - 1 || X >= param.X - 1 || param.Y >= Y - 1 || Y >= param.Y - 1) return true; else return false; }
	double distance(Node param) { return sqrt(pow(abs(param.X - X), 2) + pow(abs(param.Y - Y), 2)); }
	double dCost() {
		double result = 0;
		Node q(*this);
		while (q.parent != NULL) {
			result += q.distance(*q.parent);
			q = *(q.parent);
		}
		return result;
	}
	bool operator!=(const Node& param) { return (X != param.X || Y != param.Y); }
	bool operator==(const Node& param) { return (X == param.X && Y == param.Y); }
};

class Ghost : public Drawable {
	short destX;
	short destY;
	char map[sizeMapY][sizeMapX];//Daj mi mape Rafa³ jakoœ
	std::deque<Node> deWay;
	Sprite sprite;
	Texture texture;
	const float ghostVelocity{ 4.0f };
	Vector2f velocity{ 0.0f,0.0f };
	Mapa* mapPointer;
	short direction;

	bool findPath;

	void si();
	
public:
	double getX() { return sprite.getPosition().x; }
	double getY() { return sprite.getPosition().y; }

	Ghost(int x, int y, Mapa* map);
	~Ghost();

	void update(float destXParam, float destYParam);
	void draw(RenderTarget& target, RenderStates state) const override;
	bool switchPathFindingOnOff() { return findPath = !findPath; }
};

#endif //GHOST_H