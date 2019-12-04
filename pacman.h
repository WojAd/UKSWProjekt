#ifndef PACMAN_H
#define PACMAN_H

//#include <SFML/Graphics.hpp>
#include "mapa.h"
#include "FilePaths.h"
#include"SFML/Graphics.hpp"

//#define IMG_WIDTH 53
//#define IMG_HEIGHT 58

#define FRAME_WIDTH 40
#define FRAME_HEIGHT 40
#define IMG_WIDTH 200
#define IMG_HEIGHT 160

using namespace std;
using namespace sf;

class Pacman : public Drawable {
public:
	Pacman(float x, float y, int lives, int window_width, int window_height, Mapa* map);
	void update();
	int window_width, window_height;
	int getLives();
	Vector2f getPosition();
	Sprite getSprite() const;
private:
	Clock clock;
	IntRect textRect;
	int changeFrameStep;
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
	Mapa *map;
};

#endif
