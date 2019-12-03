#include "duch.h"


Ghost::Ghost(int x, int y, Mapa* map) {
	if (!texture.loadFromFile("ghost.png")) {
		cout << "Nie mozna otworzyc pliku ghost.png" << endl;
	}
	sprite.setTexture(texture);
	sprite.setOrigin(IMG_WIDTH / 2.0f, IMG_HEIGHT / 2.0f);
	sprite.setPosition(x, y);
	sf::Thread thread(&Ghost::si, this);
	destX = -1;
	destY = -1;
	mapPointer = map;
}

Ghost::~Ghost() {
	deWay.clear();
}

void Ghost::update(short pacmanX, short pacmanY)
{
	destX = pacmanX;
	destY = pacmanY;
	if (!deWay.empty()) {
		//Poruszanie sie sciezka
	}
}

void Ghost::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(this->sprite, state);
}

float Ghost::left() {
	return this->sprite.getPosition().x - IMG_WIDTH / 2.0f;
}

float Ghost::right() {
	return this->sprite.getPosition().x + IMG_WIDTH / 2.0f;
}

float Ghost::top() {
	return this->sprite.getPosition().y - IMG_HEIGHT / 2.0f;
}

float Ghost::bottom() {
	return this->sprite.getPosition().y + IMG_HEIGHT / 2.0f;
}

void Ghost::si() {
	while (1) {
		if (destX != -1 && findPath) {
			deque<Node> result;
			Node destination;

			/* A* path find algorithm */

			deque<Node> closed;
			deque<Node> open;

			/*________________________*/

			deWay.clear();
			for (Node q : result) deWay.push_back(q);
		}
		else {
			//do nothing
		}
	}
}