#include "pacman.h"
#include <iostream>

#define IMG_WIDTH 53
#define IMG_HEIGHT 58

Pacman::Pacman(int x, int y, int lives, int window_width, int window_height) {
	this->lives = lives;
	this->window_height = window_height;
	this->window_width = window_width;
	if (!texture.loadFromFile("pacman.png")) {
		cout << "Nie mozna otworzyc pliku." << endl;
	}
	sprite.setTexture(texture);
	sprite.setOrigin(IMG_WIDTH / 2.0f, IMG_HEIGHT / 2.0f);
	sprite.setPosition(x, y);
}

void Pacman::draw(RenderTarget& target, RenderStates state) const {
	target.draw(this->sprite, state);
}

float Pacman::left() {
	return this->sprite.getPosition().x - IMG_WIDTH / 2.0f;
}

float Pacman::right() {
	return this->sprite.getPosition().x + IMG_WIDTH / 2.0f;
}

float Pacman::top() {
	return this->sprite.getPosition().y - IMG_HEIGHT / 2.0f;
}

float Pacman::bottom() {
	return this->sprite.getPosition().y + IMG_HEIGHT / 2.0f;
}

void Pacman::update() {
	sprite.move(this->velocity);
	if (Keyboard::isKeyPressed(Keyboard::Key::Left) && left() > 0) {
		velocity.x = -pacVelocity;
		velocity.y = 0;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Right) && right() < window_width) {
		velocity.x = pacVelocity;
		velocity.y = 0;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Up) && top() > 0) {
		velocity.y = -pacVelocity;
		velocity.x = 0;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Down) && bottom() < window_height) {
		velocity.y = pacVelocity;
		velocity.x = 0;
	}
	else {
		velocity.x = 0;
		velocity.y = 0;
	}
}
