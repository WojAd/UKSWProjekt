#include "pacman.h"


Pacman::Pacman(float x, float y, int lives, int window_width, int window_height, Mapa *map) {
	this->lives = lives;
	this->window_height = window_height;
	this->window_width = window_width;
	this->map = map;
	if (!texture.loadFromFile(TEXPATH_PACMAN)) {
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
	if ((Keyboard::isKeyPressed(Keyboard::Key::Left) && left() > 0) /*&& (map->getTile(left(), sprite.getPosition().y) != WALL)*/) {
		velocity.x = -pacVelocity;
		velocity.y = 0;
	}
	else if ((Keyboard::isKeyPressed(Keyboard::Key::Right) && right() < window_width)/* && (map->getTile(right(), sprite.getPosition().y) != WALL)*/) {
		velocity.x = pacVelocity;
		velocity.y = 0;
	}
	else if ((Keyboard::isKeyPressed(Keyboard::Key::Up) && top() > 0) /*&& (map->getTile(sprite.getPosition().x, top()) != WALL)*/) {
		velocity.y = -pacVelocity;
		velocity.x = 0;
	}
	else if ((Keyboard::isKeyPressed(Keyboard::Key::Down) && bottom() < window_height) /*&& (map->getTile(sprite.getPosition().x, bottom()) != WALL)*/) {
		velocity.y = pacVelocity;
		velocity.x = 0;
	}
	else {
		velocity.x = 0;
		velocity.y = 0;
	}
}

int Pacman::getLives()
{
	return this->lives;
}

Vector2f Pacman::getPosition()
{
	return sprite.getPosition();
}

Sprite Pacman::getSprite() const {
	return sprite;
}
