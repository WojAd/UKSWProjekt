#ifndef PACMAN_H
#define PACMAN_H

#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class Pacman : public Drawable {
public:
	//Pacman();
	Pacman(int x, int y, int lives, int window_width, int window_height);
	void update();
	int window_width, window_height;
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
