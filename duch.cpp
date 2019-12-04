#include "duch.h"
#include <Windows.h>
#include <assert.h>

Ghost::Ghost(int x, int y, Mapa* map) {
	if (!texture.loadFromFile("ghost.png")) {
		cout << "Nie mozna otworzyc pliku ghost.png" << endl;
	}
	sprite.setTexture(texture);
	sprite.setOrigin(IMG_WIDTH / 2.0f, IMG_HEIGHT / 2.0f);
	sprite.setPosition(x, y);
	destX = 1;
	destY = 1;
	mapPointer = map;
	threading = false;
	threads = NULL;
	for (int y = 0; y < MAP_HEIGHT; y++)
		for (int x = 0; x < MAP_WIDTH; x++) {
			if (map->getTile(x,y) == CORRIDOR)
				this->map.push_back(Node(x, y));
		}
}

Ghost::~Ghost() {
	deWay.clear();
}

void Ghost::update(float destXParam, float destYParam)
{
	sf::Vector2u tile = mapPointer->pixelsToTilecoords(sf::Vector2f(destXParam, destYParam));
	destX = (destXParam-152)/40;
	destY = (destYParam-20)/40;
	if (threading == false) {
		if (threads != NULL && !threads->joinable()) {
			delete threads;
		}
		else if (threads != NULL && !threads->joinable()) {
			threads->join();
		}
		threading = true;
		threads = new thread(&Ghost::si, this);
	}
	
	if (!deWay.empty()) {
		//Tile 0 0 to 152, 20 (srodek)
		sf::Vector2u tile = mapPointer->pixelsToTilecoords(sf::Vector2f(getX(), getY()));
		short currTileX = tile.x;
		short currTileY = tile.y;
		short nextTileX = deWay.back().X;
		short nextTileY = deWay.back().Y;
		short currPixelX = getX();
		short currPixelY = getY();
		short nextPixelX = nextTileX * 40 + 152;
		short nextPixelY = nextTileY * 40 + 20;
		if (currPixelX == nextPixelX && currPixelY == nextPixelY) deWay.pop_back(	);
		else if (currPixelX < nextPixelX) this->sprite.move(sf::Vector2f(ghostVelocity, 0));
		else if (currPixelX > nextPixelX) this->sprite.move(sf::Vector2f(-ghostVelocity, 0));
		else if (currPixelY < nextPixelY) this->sprite.move(sf::Vector2f(0, ghostVelocity));
		else if (currPixelY > nextPixelY) this->sprite.move(sf::Vector2f(0, -ghostVelocity));
	}
}

void Ghost::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(this->sprite, state);
}

void Ghost::si() {
	short x = (getX()-152)/40;
	short y = (getY()-20)/40;
	//destX, destY
	Node destination(destX, destY, 0, NULL);
	//deque<Node> map
	deque<Node> open;
	deque<Node> closed;
	Node currNode(x, y, 0, NULL);
	closed.push_back(currNode);
	if (x > 0 && destX > 0 && y > 0 && destY > 0 && x < IMG_WIDTH && destX < IMG_WIDTH && y < IMG_HEIGHT && destY < IMG_HEIGHT && closed.back() != destination && mapPointer->getTile(destX, destY) == CORRIDOR) {
		while (closed.back() != destination) {
			for (deque<Node>::iterator i = map.begin(); i < map.end(); i++) {
				if (closed.back().isNeighbour(*i)) {
					deque<Node>::iterator found = std::find(open.begin(), open.end(), *i);
					if (found != open.end()) {
						if (found->dCost > closed.back().dCost + found->getDistance(closed.back())) {
							found->dCost = closed.back().dCost + found->getDistance(closed.back());
							found->parent = &closed.back();
						}
					}
					else {
						open.push_back(*i);
						open.back().parent = &closed.back();
						open.back().dCost = closed.back().dCost + open.back().getDistance(closed.back());
					}
				}
			}
			deque<Node>::iterator minimum = open.begin();
			for (deque<Node>::iterator i = open.begin(); i < open.end(); i++) {
				if (minimum->dCost > i->dCost) minimum = i;
			}
			closed.push_back(*minimum);
			open.erase(minimum);
		}
		Node* q = &closed.back();
		deWay.clear();
		while (q->parent != NULL) {
			deWay.push_back(*q);
			q = q->parent;
		}
	}
	Sleep(400);
	threading = false;
}

///* Data */
//sf::Vector2u tile = mapPointer->pixelsToTilecoords(sf::Vector2f(getX(), getY()));
//short x = tile.x;
//short y = tile.y;
////destX (tile), destY (tile), deque<Node> map
//deque<Node*> open;
//deque<Node*> closed;
//Node* candidate = new Node(x, y, NULL, 0);
//Node destination(destX, destY);

///* A* Star path finding */
//while (*closed.back() != destination) {
//	closed.push_back(new Node(*candidate));
//	for (Node q : map) {
//		if (q.isNeighbour(*closed.back())) {
//			for (Node* o : open) {
//				if (*o == q) {
//					if (o->parent->dCost > closed.back()->dCost) {
//						o->parent = closed.back();
//						o->dCost = o->getDistance(*closed.back()) + closed.back()->dCost;
//					}
//				}
//				else {
//					open.push_back(o);
//					open.back()->parent = closed.back();
//					open.back()->dCost = open.back()->getDistance(*closed.back()) + closed.back()->dCost;
//				}
//			}
//		}
//	}
//	assert(0);
//	assert(open.size() != 0);
//	assert(open.size() > 100);
//	candidate = open.back();
//	double distanceToDestination = candidate->getDistance(destination);
//	for (Node* q : open) {
//		if (distanceToDestination + candidate->dCost > q->getDistance(destination) + q->dCost) {
//			candidate = q;
//			distanceToDestination = candidate->getDistance(destination);
//		}
//	}
//}
///* creating deWay */
//Node way(*closed.back());
//deWay.clear();
//while (way.parent != NULL) {
//	deWay.push_back(way);
//	way = *(way.parent);
//}
//closed.clear();
//open.clear();
//Sleep(400);
//threading = false;