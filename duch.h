#ifndef GHOST_H
#define GHOST_H

using namespace std;

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <deque>
#include <iostream>
using namespace std;
using namespace sf;

#define sizeMapX 20
#define sizeMapY 20
#define IMG_WIDTH 64
#define IMG_HEIGHT 64

class Node {
public:
	short X;
	short Y;
	Node* parent;


	Node() { X = 0; Y = 0; parent = NULL; }
	Node(short X, short Y) { this->X = X; this->Y = Y; parent = NULL; }
	~Node() {};

	bool isNeighbour(Node param) { if (param.X >= X - 1 || X >= param.X - 1 || param.Y >= Y - 1 || Y >= param.Y - 1) return true; else return false; }
	double distance(Node param) { return sqrt(pow(abs(param.X - X), 2) + pow(abs(param.Y - Y), 2)); }
};

class Ghost : public Drawable {
	short destX;
	short destY;
	char map[sizeMapY][sizeMapX];//Daj mi mape Rafa� jako�
	std::deque<Node> deWay;
	Sprite sprite;
	Texture texture;
	const float ghostVelocity{ 4.0f };
	Vector2f velocity{ 0.0f,0.0f };

	void si();
	float left();
	float right();
	float top();
	float bottom();
	
public:
	double getX() { return sprite.getPosition().x; }
	double getY() { return sprite.getPosition().y; }

	Ghost(int x, int y);
	~Ghost();

	void update();
	void draw(RenderTarget& target, RenderStates state) const override;
};

#endif //GHOST_H