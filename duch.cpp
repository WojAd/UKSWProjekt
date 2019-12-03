#include "duch.h"


Ghost::Ghost(int x, int y, Mapa* param) {
	if (!texture.loadFromFile("ghost.png")) {
		cout << "Nie mozna otworzyc pliku ghost.png" << endl;
	}
	sprite.setTexture(texture);
	sprite.setOrigin(IMG_WIDTH / 2.0f, IMG_HEIGHT / 2.0f);
	sprite.setPosition(x, y);
	sf::Thread thread(&Ghost::si, this);
	map = param;
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
		deque<Node> result;
		deque<Node> map;
		for (int i = 0; i < sizeMapY; i++) {
			for (int j = 0; j < sizeMapX; j++) {
				if (this->map[i][j] == ' ') {
					map.push_back(Node(i, j));
				}
			}
		}
		Node destination;

		/* A* path find algorithm */
		
		deque<Node> closed;
		deque<Node> open;

		/*________________________*/

		deWay.clear();
		for (Node q : result) deWay.push_back(q);
	}
}