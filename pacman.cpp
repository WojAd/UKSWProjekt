#include "pacman.h"


Pacman::Pacman(float x, float y, int lives, int windowWidth, int windowHeight, Mapa *map) {
	this->lives = lives;
	this->windowHeight = windowHeight;
	this->windowWidth = windowWidth;
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
	Vector2u leftColision = map->pixelsToTilecoords(Vector2f(left(), sprite.getPosition().y));
	Vector2u rightColision = map->pixelsToTilecoords(Vector2f(right(), sprite.getPosition().y));
	Vector2u UpColision = map->pixelsToTilecoords(Vector2f(sprite.getPosition().x, top()));
	Vector2u DownColision = map->pixelsToTilecoords(Vector2f(sprite.getPosition().x, bottom()));
	if ((Keyboard::isKeyPressed(Keyboard::Key::Left) && left() > 0) && (map->getTile(leftColision.x, leftColision.y) != WALL)) {
		velocity.x = -pacVelocity;
		velocity.y = 0;
		textRect.top = FRAME_HEIGHT;
	}
	else if ((Keyboard::isKeyPressed(Keyboard::Key::Right) && right() < windowWidth) && (map->getTile(rightColision.x, rightColision.y) != WALL)) {
		velocity.x = pacVelocity;
		velocity.y = 0;
		textRect.top = 0;
	}
	else if ((Keyboard::isKeyPressed(Keyboard::Key::Up) && top() > 0) && (map->getTile(UpColision.x, UpColision.y) != WALL)) {
		velocity.y = -pacVelocity;
		velocity.x = 0;
		textRect.top = FRAME_HEIGHT * 3;
	}
	else if ((Keyboard::isKeyPressed(Keyboard::Key::Down) && bottom() < windowHeight) && (map->getTile(DownColision.x, DownColision.y) != WALL)) {
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

void Pacman::setPosition(Vector2f &pos) {
	if (pos.x > windowWidth || pos.y > windowHeight) return;
	sprite.setPosition(pos);
}

Sprite Pacman::getSprite() const {
	return sprite;
}

void Pacman::setLives(int lives) {
	if (lives > PACMAN_MAX_LIVES || lives < 0) return;
	this->lives = lives;
}

void Pacman::killPacman(){
	pacVelocity = 0;
}

void Pacman::revivePacman() {
	pacVelocity = 4.0f;
}
