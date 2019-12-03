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
	findPath = true;
}

Ghost::~Ghost() {
	deWay.clear();
}

void Ghost::update(short pacmanX, short pacmanY)
{
	
	destX = pacmanX/TILE_WIDTH;
	destY = pacmanY/TILE_HEIGHT;
	if (!deWay.empty()) {
		short currTileX = this->sprite.getPosition().x / TILE_WIDTH;
		short currTileY = this->sprite.getPosition().y / TILE_HEIGHT;
		short nextTileX = deWay.back().X;
		short nextTileY = deWay.back().Y;
		if (currTileY == currTileX) deWay.pop_back();
		else if (currTileX < nextTileX) right();
		else if (currTileX > nextTileX) left();
		else if (currTileY < nextTileY) bottom();
		else if (currTileY > nextTileY) top();
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
	/*
	while (1) {
		if (destX != -1 && findPath) {
			/* A* path find algorithm 
			short x = this->sprite.getPosition().x/TILE_WIDTH;
			short y = this->sprite.getPosition().y/TILE_HEIGHT;
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
				/* core 
				if (!open.empty()) {
					Node candidate = open.front();
					for (Node q : open) {
						if (q.dCost() < candidate.dCost())
							candidate = q;
					}
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
	}
	*/
}