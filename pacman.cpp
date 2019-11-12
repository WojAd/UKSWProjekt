#include "pacman.h"
#include <iostream>

Pacman::Pacman(int x, int y, int lives, int points) {
	this->lives = lives;
	this->points = points;
	if (!texture.loadFromFile("pacman.png")) {
		cout << "Nie mozna otworzyc pliku." << endl;
	}
	sprite.setTexture(texture);
}

void Pacman::draw(RenderTarget& target, RenderStates state) const {
	target.draw(this->sprite, state);
}