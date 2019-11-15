#include "Button.h"

namespace qiwi
{
	///////////////////////////////////////////
	//////////////Private methods//////////////
	///////////////////////////////////////////
	void Button::adjust_text_position()
	{
		sf::Vector2f position;
		position.x = shape.getPosition().x + shape.getSize().x/2 - text.getLocalBounds().left - text.getLocalBounds().width/2;
		position.y = shape.getPosition().y + shape.getSize().y/2 - text.getLocalBounds().top - text.getLocalBounds().height/2;

		text.setPosition(position);
	}

	bool Button::aimed(sf::RenderWindow &win)
	{
		sf::Vector2f world_mouse = win.mapPixelToCoords((sf::Vector2i)sf::Mouse::getPosition(win));

		if (world_mouse.x > getPosition().x && world_mouse.x < getPosition().x + getSize().x &&
			world_mouse.y > getPosition().y && world_mouse.y < getPosition().y + getSize().y)
			return true;

		return false;
	}
	///////////////////////////////////////////



	//////////////////////////////////////////
	//////////////Button methods//////////////
	//////////////////////////////////////////
	void Button::setState(bool activated)
	{
		this->_active = activated;
	}
	void Button::setSize(const sf::Vector2f &size)
	{
		setSize(size.x, size.y);
	}
	void Button::setSize(float x, float y)
	{
		shape.setSize(sf::Vector2f(x, y));

		adjust_text_position();
	}
	void Button::setTexture(const sf::Texture &texture, bool resetRect)
	{
		shape.setTexture(&texture, resetRect);
	}
	void Button::setTextureRect(const sf::IntRect &rect)
	{
		shape.setTextureRect(rect);
	}
	void Button::setPosition(float x, float y)
	{
		setPosition(sf::Vector2f(x, y));
	}
	void Button::setPosition(const sf::Vector2f &position)
	{
		shape.setPosition(position);

		adjust_text_position();
	}
	void Button::move(float offsetX, float offsetY)
	{
		move(sf::Vector2f(offsetX, offsetY));
	}
	void Button::move(const sf::Vector2f &offset)
	{
		shape.move(offset);
		text.move(offset);
	}
	void Button::setColor(const sf::Color &color)
	{
		shape.setFillColor(color);
	}
	//////////////////////////////////////////



	////////////////////////////////////////
	//////////////Text methods//////////////
	////////////////////////////////////////
	void Button::setTextOn(bool text_on, sf::Font *font)
	{
		this->_text_on = text_on;

		if (font != nullptr)
		{
			text.setFont(*font);

			adjust_text_position();
		}
	}
	void Button::setTextString(const sf::String &str)
	{
		text.setString(str);

		adjust_text_position();
	}
	void Button::setTextFont(const sf::Font &font)
	{
		text.setFont(font);

		adjust_text_position();
	}
	void Button::setTextCharSize(unsigned int size)
	{
		text.setCharacterSize(size);

		adjust_text_position();
	}
	void Button::setTextLineSpacing(float spacingFactor)
	{
		text.setLineSpacing(spacingFactor);

		adjust_text_position();
	}
	void Button::setTextLetterSpacing(float spacingFactor)
	{
		text.setLetterSpacing(spacingFactor);

		adjust_text_position();
	}
	void Button::setTextStyle(sf::Uint32 style)
	{
		text.setStyle(style);

		adjust_text_position();
	}
	void Button::setTextColor(const sf::Color &color)
	{
		text.setFillColor(color);
	}
	void Button::setTextOutlineColor(const sf::Color &color)
	{
		text.setOutlineColor(color);
	}
	void Button::setTextOutlineThickness(float thickness)
	{
		text.setOutlineThickness(thickness);

		adjust_text_position();
	}
	////////////////////////////////////////



	/////////////////////////////////////////
	//////////////Color methods//////////////
	/////////////////////////////////////////
	void Button::setIdleColor(const sf::Color &color)
	{
		_idle_color = color;
	}
	void Button::setHoverColor(const sf::Color &color)
	{
		_hover_color = color;
	}
	void Button::setPressColor(const sf::Color &color)
	{
		_press_color = color;
	}
	void Button::setIdleTextColor(const sf::Color &color)
	{
		_idle_text_color = color;
	}
	void Button::setHoverTextColor(const sf::Color &color)
	{
		_hover_text_color = color;
	}
	void Button::setPressTextColor(const sf::Color &color)
	{
		_press_text_color = color;
	}
	/////////////////////////////////////////



	///////////////////////////////////////////
	//////////////Overall methods//////////////
	///////////////////////////////////////////
	void Button::update(sf::RenderWindow &win)
	{
		_hovered = aimed(win);
		_clicked = false;

		if (!_active)
		{
			shape.setFillColor(_press_color);
			text.setFillColor(_press_text_color);
		}
		else
		{
			if (win.hasFocus())
			{
				if (!_held)
				{
					if (_hovered)
					{
						if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && win.hasFocus())
						{
							_held = true;
							shape.setFillColor(_press_color);
							text.setFillColor(_press_text_color);
						}
						else
						{
							shape.setFillColor(_hover_color);
							text.setFillColor(_hover_text_color);
						}
					}
					else
					{
						shape.setFillColor(_idle_color);
						text.setFillColor(_idle_text_color);
					}
				}
				else
				{
					if (_hovered)
					{
						if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && win.hasFocus())
						{
							_held = false;
							_clicked = true;
							shape.setFillColor(_hover_color);
							text.setFillColor(_hover_text_color);
						}
					}
					else
					{
						if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && win.hasFocus())
						{
							_held = false;
							shape.setFillColor(_idle_color);
							text.setFillColor(_idle_text_color);
						}
					}
				}
			}
			else
			{
				shape.setFillColor(_idle_color);
				text.setFillColor(_idle_text_color);
			}
		}
	}
	void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		target.draw(shape, states);
		if (_text_on)
			target.draw(text, states);
	}
	///////////////////////////////////////////



	////////////////////////////////////////
	//////////////Constructors//////////////
	////////////////////////////////////////
	Button::Button(const sf::Vector2f& size, const sf::Vector2f& position, bool activated, bool text_on)
	{
		this->_active = activated;
		this->_text_on = text_on;

		this->_hovered = false;
		this->_held = false;
		this->_clicked = false;

		this->shape.setSize(size);//Own setTextString function will adjust text anyway
		this->shape.setPosition(position);

		this->setTextString("NULL");

		this->setIdleColor(sf::Color(200, 200, 200));
		this->setHoverColor(sf::Color(255, 255, 255));
		this->setPressColor(sf::Color(100, 100, 100));
		this->setIdleTextColor(sf::Color(20, 20, 20));
		this->setHoverTextColor(sf::Color(40, 40, 40));
		this->setPressTextColor(sf::Color(0, 0, 0));
	}
}
