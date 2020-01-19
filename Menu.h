#ifndef MENU_H
#define MENU_H

#include "Button.h"
#include "FilePaths.h"

#define TITLE_SIZE 48
#define BUTTON_TEXT_SIZE 28

#define BUTTON_WIDTH 300
#define BUTTON_HEIGHT 50

#define BUTTON_PLAY_Y 200
#define BUTTON_RESET_Y 300
#define BUTTON_EXIT_Y 400

class Menu
{
private:
	sf::RenderWindow *win = nullptr;
	sf::Text txt_title;

	//Fonts
	sf::Font fnt_default;

	qiwi::Button *play = nullptr;
	qiwi::Button *reset = nullptr;
	qiwi::Button *exit = nullptr;
public:
	Menu(sf::RenderWindow &win);
	~Menu();

	void handleEvents();
	void update();
	void draw();

	bool go_to_game = false;
	bool go_reset = false;
};

#endif