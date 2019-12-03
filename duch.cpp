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
}

Ghost::~Ghost() {
	deWay.clear();
}

void Ghost::update(float destXParam, float destYParam)
{
	sf::Vector2u tile = mapPointer->pixelsToTilecoords(sf::Vector2f(destXParam, destYParam));
	destX = tile.x;
	destY = tile.y;
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
		cout << " " << this << " ";
		sf::Vector2u tile = mapPointer->pixelsToTilecoords(sf::Vector2f(getX(), getY()));
		short x = tile.x;
		short y = tile.y;
		if (destX > 0 && destX < 40 && destY > 0 && destY < 40 && x > 0 && x < 40 && y > 0 && y < 40 && mapPointer->getTile(destX, destY) != WALL) {
			// A* path find algorithm 
			Node destination(destX, destY);
			deque<Node> closed;
			deque<Node> open;
			closed.push_back(Node(x, y));
			if (mapPointer->getTile(closed.back().X - 1, closed.back().Y) == CORRIDOR)
				open.push_back(Node(closed.back().X - 1, closed.back().Y, &closed.back()));
			if (mapPointer->getTile(closed.back().X + 1, closed.back().Y) == CORRIDOR)
				open.push_back(Node(closed.back().X + 1, closed.back().Y, &closed.back()));
			if (mapPointer->getTile(closed.back().X, closed.back().Y - 1) == CORRIDOR)
				open.push_back(Node(closed.back().X, closed.back().Y - 1, &closed.back()));
			if (mapPointer->getTile(closed.back().X, closed.back().Y + 1) == CORRIDOR)
				open.push_back(Node(closed.back().X, closed.back().Y + 1, &closed.back()));
			while (closed.back() != destination && !open.empty()) {
				// core
				if (!open.empty()) {
					Node candidate = open.front();
					for (Node q : open) {
						if (q.dCost() + q.distance(Node(destX, destY)) < candidate.dCost() + candidate.distance(Node(destX, destY)))
							candidate = q;
					}
					while (open.front() != candidate) {
						open.push_back(open.front());
						open.pop_front();
					}
					open.pop_front();
					closed.push_back(candidate);
					//Warto sie zastanowic nad eliminowaniem istniejacych nodesow
					if (mapPointer->getTile(closed.back().X - 1, closed.back().Y) == CORRIDOR)
						open.push_back(Node(closed.back().X - 1, closed.back().Y, &closed.back()));
					if (mapPointer->getTile(closed.back().X + 1, closed.back().Y) == CORRIDOR)
						open.push_back(Node(closed.back().X + 1, closed.back().Y, &closed.back()));
					if (mapPointer->getTile(closed.back().X, closed.back().Y - 1) == CORRIDOR)
						open.push_back(Node(closed.back().X, closed.back().Y - 1, &closed.back()));
					if (mapPointer->getTile(closed.back().X, closed.back().Y + 1) == CORRIDOR)
						open.push_back(Node(closed.back().X, closed.back().Y + 1, &closed.back()));
				}
				if (open.size() > 200) {
					threading = false;
					return;
				}
			}

			deque<Node> result;
			Node currNode(closed.back());
			result.push_back(currNode);
			while (currNode.parent != NULL) {
				currNode = *currNode.parent;
				result.push_back(currNode);
			}
			deWay.clear();
			for (Node q : result) deWay.push_back(q);
		}
		else {
			//do nothing
		}
		Sleep(400);
		threading = false;
}