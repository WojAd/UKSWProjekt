#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>

namespace qiwi
{
	class Button : public sf::Drawable
	{
	private:		
		bool _active;
		bool _text_on;
		void adjust_text_position();

		bool _hovered;
		bool _held;
		bool _clicked;
		bool aimed(sf::RenderWindow &win);

		sf::Color _idle_color;
		sf::Color _hover_color;
		sf::Color _press_color;

		sf::Color _idle_text_color;
		sf::Color _hover_text_color;
		sf::Color _press_text_color;

		sf::RectangleShape shape;
		sf::Text text;

	protected:
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	public:
		/*Setters*/
		void setState(bool activated);
		void setSize(const sf::Vector2f &size);
		void setSize(float x, float y);
		void setTexture(const sf::Texture &texture, bool resetRect = false);
		void setTextureRect(const sf::IntRect &rect);
		void setPosition(float x, float y);
		void setPosition(const sf::Vector2f &position);
		void move(float offsetX, float offsetY);
		void move(const sf::Vector2f &offset);
		void setColor(const sf::Color &color);

		void setTextOn(bool text_on = false,sf::Font *font = nullptr);
		void setTextString(const sf::String &str);
		void setTextFont(const sf::Font &font);
		void setTextCharSize(unsigned int size);
		void setTextLineSpacing(float spacingFactor);
		void setTextLetterSpacing(float spacingFactor);
		void setTextStyle(sf::Uint32 style);
		void setTextColor(const sf::Color &color);
		void setTextOutlineColor(const sf::Color &color);
		void setTextOutlineThickness(float thickness);

		void setIdleColor(const sf::Color &color);
		void setHoverColor(const sf::Color &color);
		void setPressColor(const sf::Color &color);

		void setIdleTextColor(const sf::Color &color);
		void setHoverTextColor(const sf::Color &color);
		void setPressTextColor(const sf::Color &color);

		/*Getters*/
		bool getState() { return _active; };
		const sf::Vector2f &getSize() {	return shape.getSize();	}
		const sf::Texture *getTexture() { return shape.getTexture(); }
		const sf::IntRect &getTextureRect() { return shape.getTextureRect(); }
		const sf::Vector2f &getPosition() { return shape.getPosition(); }
		const sf::FloatRect &getShapeBounds() { return shape.getLocalBounds(); }

		bool isTextOn() const { return _text_on; }
		const sf::String &getTextString() const { return text.getString(); }
		const sf::Font &getTextFont() const { return *(text.getFont()); }
		const unsigned int getTextCharSize() const { return text.getCharacterSize(); }
		float getTextLineSpacing() const { return text.getLineSpacing(); }
		float getTextLetterSpacing() const { return text.getLetterSpacing(); }
		const sf::Uint32 &getTextStyle() const { return text.getStyle(); }
		const sf::Color &getTextColor() const { return text.getFillColor(); }
		const sf::Color &getTextOutlineColor() const { return text.getOutlineColor(); }
		const sf::Vector2f &getTextPosition() const { return text.getPosition(); }
		float getTextOutlineThickness() const { return text.getOutlineThickness(); }
		const sf::FloatRect &getTextBounds() const { return text.getLocalBounds(); }

		const sf::Color &getIdleColor() const { return _idle_color; }
		const sf::Color &getHoverColor() const { return _hover_color; }
		const sf::Color &getPressColor() const { return _press_color; }

		const sf::Color &getIdleTextColor() const { return _idle_text_color; }
		const sf::Color &getHoverTextColor() const { return _hover_text_color; }
		const sf::Color &getPressTextColor() const { return _press_text_color; }

		/*Constructors*/
		Button() : Button(sf::Vector2f(200, 100), sf::Vector2f(0, 0)) {};
		Button(const sf::Vector2f& size, const sf::Vector2f& position, bool activated = true, bool text_on = true);

		/*Overall*/
		void update(sf::RenderWindow &win);
		bool hovered() { return _hovered; }
		bool held() { return _held; }
		bool clicked() { return _clicked; }
	};
}

#endif