#include "duch.h"
#include <Windows.h>



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
	destX = (destXParam-132)/40;
	destY = (destYParam)/40;
	if (threading == false && newDeWay.empty()) {
		if (threads != NULL && !threads->joinable()) {
			delete threads;
		}
		else if (threads != NULL && !threads->joinable()) {
			threads->join();
		}
		threading = true;
		threads = new thread(&Ghost::si, this);
	}
	if (!newDeWay.empty() && threading == false) {
		if (!deWay.empty() && newDeWay.size() - deWay.size() / 4 >= deWay.size() && equal(deWay.begin(), deWay.end()-deWay.size()/4, newDeWay.begin())) newDeWay.clear();
		else {
			sf::Vector2u tile = mapPointer->pixelsToTilecoords(sf::Vector2f(getX(), getY()));
			short currTileX = tile.x;
			short currTileY = tile.y;
			Node currNode(currTileX, currTileY);
			for (deque<Node>::iterator i = newDeWay.begin(); i < newDeWay.end(); i++) {
				if (currNode == *i) {
					newDeWay.erase(i, newDeWay.end());
					break;
				}
			}
			/*if (!currNode.isNeighbour(newDeWay.back()) && currNode.X != newDeWay.back().X && currNode.Y != newDeWay.back().Y) {
				Node candidate;
				for (deque<Node>::iterator i = map.begin(); i < map.end(); i++) {
					if ((currNode.X == i->X && newDeWay.back().Y == i->Y) || (newDeWay.back().X == i->X && currNode.Y == i->Y)) {
						candidate = *i;
						break;
					}
				}
				newDeWay.push_back(candidate);
			}*/
			deWay = newDeWay;
			newDeWay.clear();
		}

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
		Node currNode(currTileX, currTileY);
		Node nextNode(nextTileX, nextTileY);
		
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

	short x = (getX() - 132) / 40;
	short y = (getY()) / 40;
	//destX, destY
	Node destination(destX, destY, 0, NULL);
	//deque<Node> map
	deque<Node> open;
	deque<Node> closed;
	open.clear();
	closed.clear();
	Node currNode(x, y, 0, NULL);
	closed.push_back(currNode);
	if ((deWay.empty() || destination != deWay.front()) && x > 0 && destX > 0 && y > 0 && destY > 0 && x < IMG_WIDTH && destX < IMG_WIDTH && y < IMG_HEIGHT && destY < IMG_HEIGHT && closed.back() != destination && mapPointer->getTile(destX, destY) == CORRIDOR) {
		while (closed.back() != destination) {
			for (deque<Node>::iterator i = map.begin(); i < map.end(); i++) {
				if (closed.back().isNeighbour(*i)) {
					deque<Node>::iterator found = std::find(open.begin(), open.end(), *i);
					if (found != open.end()) {
						if (found->dCost + found->getDistance(destination) > closed.back().dCost + found->getDistance(closed.back()) + found->getDistance(destination)) {
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
				if (minimum->dCost + minimum->getDistance(destination) > i->dCost + i->getDistance(destination)) minimum = i;
			}
			if (closed.size() > 200) {
				Sleep(100);
				threading = false;
				return;
			}
			closed.push_back(*minimum);
			open.erase(minimum);
		}
		Node* q = &closed.back();
		newDeWay.push_back(*q);
		while (q->parent != NULL) {
			q = q->parent;
			newDeWay.push_back(*q);
		}
	}
	threading = false;
	Sleep(500);
}

Sprite Ghost::getSprite() const {
	return sprite;
}
