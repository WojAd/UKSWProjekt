#include "duch.h"


Ghost::Ghost(int x, int y) {
	

	if (!texture.loadFromFile("ghost.png")) {}
	sprite.setTexture(texture);
	sprite.setOrigin(0, 0);
	sprite.setPosition(x, y);

	sf::Thread thread(&Ghost::si, this);
}

Ghost::~Ghost() {
	deWay.clear();
}

void Ghost::run()
{

}

void Ghost::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(this->sprite, state);
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

GhostManager::GhostManager()
{
	for (short i = 0; i < 5; i++) {
		Ghost* newGhost = new Ghost(0, 0);
		ghosts.push_back(*newGhost);
		delete newGhost;
	}
}

GhostManager::~GhostManager()
{
	ghosts.clear();
}

void GhostManager::updateDestination()
{
	deque<Node> nodes;
}
