#include "duch.h"
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
	findPath = false;
}

Ghost::~Ghost() {
	deWay.clear();
}

void Ghost::update(float destXParam, float destYParam)
{
	sf::Vector2u tile = mapPointer->pixelsToTilecoords(sf::Vector2f(destXParam, destYParam));
	destX = tile.x;
	destY = tile.y;
	if (!findPath) {
		findPath = true;
		thread t(&Ghost::si, this);
		t.join();
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
		if (currPixelX == nextPixelX && currPixelY == nextPixelY) deWay.pop_back();
		else if (currPixelX < nextPixelX) this->sprite.move(sf::Vector2f(4.0f, 0));
		else if (currPixelX > nextPixelX) this->sprite.move(sf::Vector2f(-4.0f, 0));
		else if (currPixelY < nextPixelY) this->sprite.move(sf::Vector2f(0, 4.0f));
		else if (currPixelY > nextPixelY) this->sprite.move(sf::Vector2f(0, -4.0f));
	}
}

void Ghost::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(this->sprite, state);
}

void Ghost::si() {
	cout << "thread" << endl;
		sf::Vector2u tile = mapPointer->pixelsToTilecoords(sf::Vector2f(getX(), getY()));
		short x = tile.x;
		short y = tile.y;
		if (destX > 0 && destX < 40 && destY > 0 && destY < 40 && x > 0 && x < 40 && y > 0 && y < 40 && findPath && deWay.empty()) {
			// A* path find algorithm 
			Node destination(destX,destY);
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
					if (mapPointer->getTile(closed.back().X - 1, closed.back().Y) == CORRIDOR)
						open.push_back(Node(closed.back().X - 1, closed.back().Y, &closed.back()));
					if (mapPointer->getTile(closed.back().X + 1, closed.back().Y) == CORRIDOR)
						open.push_back(Node(closed.back().X + 1, closed.back().Y, &closed.back()));
					if (mapPointer->getTile(closed.back().X, closed.back().Y - 1) == CORRIDOR)
						open.push_back(Node(closed.back().X, closed.back().Y - 1, &closed.back()));
					if (mapPointer->getTile(closed.back().X, closed.back().Y + 1) == CORRIDOR)
						open.push_back(Node(closed.back().X, closed.back().Y + 1, &closed.back()));
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
		findPath = false;
	
}