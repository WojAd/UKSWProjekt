#include "Menu.h"

Menu::Menu(sf::RenderWindow &win)
{
	this->win = &win;

	if (!fnt_default.loadFromFile(FONTPATH_DEFAULT))
	{
		win.close();
		getchar();
	}
	txt_title.setFont(fnt_default);
	txt_title.setFillColor(sf::Color::White);
	txt_title.setCharacterSize(TITLE_SIZE);
	txt_title.setString(L"PACMAN");
	sf::Vector2f txt_size;
	txt_size.x = txt_title.getLocalBounds().left + txt_title.getLocalBounds().width;
	txt_size.y = txt_title.getLocalBounds().top + txt_title.getLocalBounds().height;
	txt_title.setPosition(sf::Vector2f(WINDOW_WIDTH/2 - txt_size.x/2, 10));


	play = new qiwi::Button(sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT), sf::Vector2f(WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2, BUTTON_PLAY_Y));
	play->setTextFont(fnt_default);
	play->setTextCharSize(BUTTON_TEXT_SIZE);
	play->setIdleColor(sf::Color(128, 128, 128));
	play->setHoverColor(sf::Color(200, 200, 200));
	play->setPressColor(sf::Color(50, 50, 50));
	play->setTextString(L"Graj");

	reset = new qiwi::Button(sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT), sf::Vector2f(WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2, BUTTON_RESET_Y));
	reset->setTextFont(fnt_default);
	reset->setTextCharSize(BUTTON_TEXT_SIZE);
	reset->setIdleColor(sf::Color(128, 128, 128));
	reset->setHoverColor(sf::Color(200, 200, 200));
	reset->setPressColor(sf::Color(50, 50, 50));
	reset->setTextString(L"Zresetuj");

	exit = new qiwi::Button(sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT), sf::Vector2f(WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2, BUTTON_EXIT_Y));
	exit->setTextFont(fnt_default);
	exit->setTextCharSize(BUTTON_TEXT_SIZE);
	exit->setIdleColor(sf::Color(128, 128, 128));
	exit->setHoverColor(sf::Color(200, 200, 200));
	exit->setPressColor(sf::Color(50, 50, 50));
	exit->setTextString(L"Wyjœcie");
}

Menu::~Menu()
{
	delete play;
	delete reset;
	delete exit;
}

void Menu::handleEvents()
{
	sf::Event ev;
	while (win->pollEvent(ev))
	{
		switch (ev.type)
		{
		case sf::Event::Closed:
			win->close();
			break;
		default:
			break;
		}
	}
}

void Menu::update()
{
	play->update(*win);
	reset->update(*win);
	exit->update(*win);

	if (play->clicked())
		go_to_game = true;
	else if (reset->clicked())
		go_reset = true;
	else if (exit->clicked())
		win->close();
}

void Menu::draw()
{
	win->clear(sf::Color::Blue);

	win->draw(txt_title);
	win->draw(*play);
	win->draw(*reset);
	win->draw(*exit);
}