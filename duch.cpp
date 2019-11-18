#include "duch.h"


Ghost::Ghost(char* pacmanX, char* pacmanY, char map[sizeMapY][sizeMapX]) {
	this->pacmanX = pacmanX;
	this->pacmanY = pacmanY;
	for (short i = 0; i < sizeMapY; i++) {
		for (short j = 0; j < sizeMapX; j++) {
			this->map[i][j] = map[i][j];
		}
	}
	sf::Thread thread();
}

Ghost::~Ghost() {
	deWay.clear();
}

void Ghost::si() {
	while (1) {
		if (pacmanX == NULL || pacmanY == NULL) { continue; }
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