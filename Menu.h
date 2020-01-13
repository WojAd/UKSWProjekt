#ifndef MENU_H
#define MENU_H

#include "Button.h"

class Menu
{
private:
	sf::RenderWindow *win = nullptr;
	sf::Text txt_title;
public:
	Menu(sf::RenderWindow &win);
	~Menu();

	void handleEvents();
	void update();
	void draw();
};

#endif