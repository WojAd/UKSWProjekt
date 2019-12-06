#include "pacman.h"


Pacman::Pacman(float x, float y, int lives, int window_width, int window_height, Mapa *map) {
	this->lives = lives;
	this->window_height = window_height;
	this->window_width = window_width;
	this->map = map;
	textRect = IntRect(0, 0, FRAME_WIDTH, FRAME_HEIGHT);
	changeFrameStep = FRAME_WIDTH;
	if (!texture.loadFromFile(TEXPATH_PACMAN)) {
		cout << "Nie mozna otworzyc pliku." << endl;
	}
	sprite.setTexture(texture);
	sprite.setTextureRect(textRect);
	sprite.setOrigin(FRAME_WIDTH / 2.0f, FRAME_HEIGHT / 2.0f);
	sprite.setPosition(x, y);
}

void Pacman::draw(RenderTarget& target, RenderStates state) const {
	target.draw(this->sprite, state);
}

float Pacman::left() {
	return this->sprite.getPosition().x - FRAME_WIDTH / 2.0f;
}

float Pacman::right() {
	return this->sprite.getPosition().x + FRAME_WIDTH / 2.0f;
}

float Pacman::top() {
	return this->sprite.getPosition().y - FRAME_HEIGHT / 2.0f;
}

float Pacman::bottom() {
	return this->sprite.getPosition().y + FRAME_HEIGHT / 2.0f;
}

void Pacman::update() {
	sprite.move(this->velocity);
	if (clock.getElapsedTime().asSeconds() > 1.0f / 10.0f){
		if ((textRect.left == IMG_WIDTH - FRAME_WIDTH && changeFrameStep > 0) || (textRect.left == 0 && changeFrameStep < 0)) {
			changeFrameStep *= -1;
		}
		textRect.left += changeFrameStep;
		sprite.setTextureRect(textRect);
		clock.restart();
	}
	if ((Keyboard::isKeyPressed(Keyboard::Key::Left) && left() > 0) /*&& (map->getTile(left(), sprite.getPosition().y) != WALL)*/) {
		velocity.x = -pacVelocity;
		velocity.y = 0;
		textRect.top = FRAME_HEIGHT;
	}
	else if ((Keyboard::isKeyPressed(Keyboard::Key::Right) && right() < window_width)/* && (map->getTile(right(), sprite.getPosition().y) != WALL)*/) {
		velocity.x = pacVelocity;
		velocity.y = 0;
		textRect.top = 0;
	}
	else if ((Keyboard::isKeyPressed(Keyboard::Key::Up) && top() > 0) /*&& (map->getTile(sprite.getPosition().x, top()) != WALL)*/) {
		velocity.y = -pacVelocity;
		velocity.x = 0;
		textRect.top = FRAME_HEIGHT * 3;
	}
	else if ((Keyboard::isKeyPressed(Keyboard::Key::Down) && bottom() < window_height) /*&& (map->getTile(sprite.getPosition().x, bottom()) != WALL)*/) {
		velocity.y = pacVelocity;
		velocity.x = 0;
		textRect.top = FRAME_HEIGHT * 2;
	}
	else {
		velocity.x = 0;
		velocity.y = 0;
	}
}

int Pacman::getLives() {
	return this->lives;
}

Vector2f Pacman::getPosition() {
	return sprite.getPosition();
}

Sprite Pacman::getSprite() const {
	return sprite;
}

void Pacman::setLives(int lives) {
	if (lives > PACMAN_MAX_LIVES || lives < 0) return;
	this->lives = lives;
}
