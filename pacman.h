#ifndef PACMAN_H
#define PACMAN_H

#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class Pacman : public Drawable {
public:
	Pacman();
	Pacman(int x, int y, int lives, int points);
private:
	Texture texture;
	Sprite sprite;
	int points;
	int lives;
	const float PacVelocity{ 4.0f };
	Vector2f velocity{ 0.0f,0.0f };
	void draw(RenderTarget& target, RenderStates state) const override;
};

#endif
