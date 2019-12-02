#ifndef PACMAN_H
#define PACMAN_H

#include <SFML/Graphics.hpp>
#include "mapa.h"
using namespace std;
using namespace sf;

class Pacman : public Drawable {
public:
	//Pacman();
	Pacman(float x, float y, int lives, int window_width, int window_height);
	void update();
	int window_width, window_height;
	int getLives();
	//Mapa map;
	Vector2f getPosition();
private:
	Texture texture;
	Sprite sprite;
	int lives;
	const float pacVelocity{ 4.0f };
	Vector2f velocity{ 0.0f,0.0f };
	void draw(RenderTarget& target, RenderStates state) const override;
	float left();
	float right();
	float top();
	float bottom();
};

#endif
