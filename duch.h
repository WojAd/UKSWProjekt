#ifndef GHOST_H
#define GHOST_H

using namespace std;

#include <SFML/Graphics.hpp>
#include <deque>
#include <iostream>
#include <thread>
#include <algorithm>
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
	double dCost;

	Node() { X = 0; Y = 0; parent = NULL; dCost = 0; }
	Node(short X, short Y) { this->X = X; this->Y = Y; parent = NULL; dCost = 0; }
	Node(short X, short Y, Node* param) { this->X = X; this->Y = Y; parent = param; dCost = 0; }
	Node(const Node& param) { X = param.X; Y = param.Y; parent = param.parent; dCost = param.dCost; }
	Node(short X, short Y, short dCost, Node* param) { this->X = X; this->Y = Y; parent = param; this->dCost = dCost; }
	~Node() {};

	bool isNeighbour(Node param) { if (((param.X == X - 1 || X == param.X - 1) && param.Y == Y) || (param.X == X && (param.Y == Y - 1 || Y == param.Y - 1))) return true; else return false; }
	double getDistance(Node param) { return sqrt(pow(abs(param.X - X), 2) + pow(abs(param.Y - Y), 2)); }
	bool operator!=(const Node& param) const { return (X != param.X || Y != param.Y); }
	bool operator==(const Node& param) const { return (X == param.X && Y == param.Y); }
};

class Ghost : public Drawable {
	short destX;
	short destY;
	deque<Node> map;
	std::deque<Node> deWay;
	std::deque<Node> newDeWay;
	Sprite sprite;
	Texture texture;
	const float ghostVelocity{ 4.0f };
	Vector2f velocity{ 0.0f,0.0f };
	Mapa* mapPointer;
	short direction;
	thread* threads;

	void si();

	bool threading;
	
public:
	double getX() { return sprite.getPosition().x; }
	double getY() { return sprite.getPosition().y; }
	sf::Vector2f getPosition() { return sprite.getPosition(); }
	void setPosition(sf::Vector2f param) { sprite.setPosition(param); deWay.clear(); }

	Ghost(int x, int y, Mapa* map);
	~Ghost();

	void update(float destXParam, float destYParam);
	void draw(RenderTarget& target, RenderStates state) const override;
	Sprite getSprite() const;
};

#endif //GHOST_H