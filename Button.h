#ifndef BUTTON_H
#define BUTTON_H

/** \file Button.h
 * Plik naglowkowy dla klasy przycisku klikanego myszk�.
 */

#include <SFML/Graphics.hpp>

namespace qiwi
{
	/**
	* Klasa reprezentujaca przycisk klikany myszk�
	* @author Rafa� �wi�der
	*/
	class Button : public sf::Drawable
	{
	private:		
		bool _active;/**< Aktywno�� guzika*/
		bool _text_on;/**< Wy�wietlanie tekstu na guziku*/
		/**
		* Dopasowanie pozycji tekstu w guziku
		* @author Rafa� �wi�der
		*/
		void adjust_text_position();

		bool _hovered;/**< Najechano kursorem*/
		bool _held;/**< Wci�ni�to przycisk*/
		bool _clicked;/**< Klikni�to guzik*/
		/**
		* Namierzenie guzika kursorem
		* /param win - okno programu
		* @return Prawda - je�eli namierzono, a w przeciwnym wypadku fa�sz
		* @author Rafa� �wi�der
		*/
		bool aimed(sf::RenderWindow &win);

		sf::Color _idle_color;/**< Kolor guzika w spoczynku*/
		sf::Color _hover_color;/**< Kolor guzika po najechaniu*/
		sf::Color _press_color;/**< Kolor guzika przy wci�ni�ciu*/

		sf::Color _idle_text_color;/**< Kolor tekstu guzika w spoczynku*/
		sf::Color _hover_text_color;/**< Kolor tekstu guzika po najechaniu*/
		sf::Color _press_text_color;/**< Kolor tekstu guzika przy wci�ni�ciu*/

		sf::RectangleShape shape;/**< Kszta�t guzika do wyrysowania w oknie*/
		sf::Text text;/**< Tekst wy�wietlany na guziku*/

	protected:
		/**
		* Rysowanie guzika
		* /param target - okno, w kt�rym guzik ma zosta� wyrysowany
		* /param states - dodatkowe opcje rysowania
		* @author Rafa� �wi�der
		*/
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	public:
		/**
		* Ustawienie aktywno�ci guzika
		* /param activated - prawda:guzik aktywny, fa�sz:nieaktywny
		* @author Rafa� �wi�der
		*/
		void setState(bool activated);
		/**
		* Rozmiar guzika
		* /param size - Wektor 2D z wymiarami dla guzika
		* @author Rafa� �wi�der
		*/
		void setSize(const sf::Vector2f &size);
		/**
		* Rozmiar guzika
		* /param x - Szeroko�� guzika
		* /param y - Wysoko�� guzika
		* @author Rafa� �wi�der
		*/
		void setSize(float x, float y);
		/**
		* Tekstura guzika
		* /param texture - Tekstura guzika
		* /param resetRect - Wy�wietlanie ca�o�ci tekstury
		* @author Rafa� �wi�der
		*/
		void setTexture(const sf::Texture &texture, bool resetRect = false);
		/**
		* Fragment tekstury guzika
		* /param rect - Po�o�enie i wymiary fragmentu tekstury do wy�wietlenia
		* @author Rafa� �wi�der
		*/
		void setTextureRect(const sf::IntRect &rect);
		/**
		* Ustawianie pozycji guzika
		* /param x - Szeroko��
		* /param y - Wysoko��
		* @author Rafa� �wi�der
		*/
		void setPosition(float x, float y);
		/**
		* Ustawianie pozycji guzika
		* /param position - Wektor 2D z koordynatami pozycji dla guzika
		* @author Rafa� �wi�der
		*/
		void setPosition(const sf::Vector2f &position);
		/**
		* Przemieszczenie guzika
		* /param offsetX - Przemieszczenie w osi X
		* /param offsetY - Przemieszczenie w osi Y
		* @author Rafa� �wi�der
		*/
		void move(float offsetX, float offsetY);
		/**
		* Przemieszczenie guzika
		* /param offset - Wektor 2D o jaki ma si� przemie�ci� guzik
		* @author Rafa� �wi�der
		*/
		void move(const sf::Vector2f &offset);
		/**
		* Ustawianie koloru guzika
		* /param color - Kolor dla guzika
		* @author Rafa� �wi�der
		*/
		void setColor(const sf::Color &color);

		/**
		* Wy�wietlanie tekstu na guziku
		* /param text_on - W��czenie tekstu
		* /param font - Czcionka dla tekstu na guziku
		* @author Rafa� �wi�der
		*/
		void setTextOn(bool text_on = false,sf::Font *font = nullptr);
		/**
		* Zmiana tekstu na guziku
		* /param str - Tekst dla guzika
		* @author Rafa� �wi�der
		*/
		void setTextString(const sf::String &str);
		/**
		* Ustawianie czcionki dla tekstu guzika
		* /param font - Czcionka dla guzika
		* @author Rafa� �wi�der
		*/
		void setTextFont(const sf::Font &font);
		/**
		* Ustawianie rozmiaru tekstu guzika
		* /param size - Rozmiar tekstu
		* @author Rafa� �wi�der
		*/
		void setTextCharSize(unsigned int size);
		/**
		* Ustawianie odst�pu pomi�dzy liniami tekstu
		* /param spacingFactor - Wielko�� odst�pu
		* @author Rafa� �wi�der
		*/
		void setTextLineSpacing(float spacingFactor);
		/**
		* Ustawianie odst�pu pomi�dzy literami tekstu
		* /param spacingFactor - Wielko�� odst�pu
		* @author Rafa� �wi�der
		*/
		void setTextLetterSpacing(float spacingFactor);
		/**
		* Ustawianie stylu dla tekstu
		* /param style - Styl dla tekstu
		* @author Rafa� �wi�der
		*/
		void setTextStyle(sf::Uint32 style);
		/**
		* Ustawianie koloru dla tekstu na guziku
		* /param color - Kolor dla tekstu guzika
		* @author Rafa� �wi�der
		*/
		void setTextColor(const sf::Color &color);
		/**
		* Ustawianie koloru obw�dki tekstu
		* /param color - Kolor dla obw�dki
		* @author Rafa� �wi�der
		*/
		void setTextOutlineColor(const sf::Color &color);
		/**
		* Ustawianie grubo�ci obw�dki tekstu
		* /param thickness - Grubo�� obw�dki
		* @author Rafa� �wi�der
		*/
		void setTextOutlineThickness(float thickness);


		/**
		* Ustawianie koloru guzika dla spoczynku
		* /param color - Kolor dla guzika
		* @author Rafa� �wi�der
		*/
		void setIdleColor(const sf::Color &color);
		/**
		* Ustawianie koloru guzika dla najechania kursorem
		* /param color - Kolor dla guzika
		* @author Rafa� �wi�der
		*/
		void setHoverColor(const sf::Color &color);
		/**
		* Ustawianie koloru guzika dla wci�ni�cia
		* /param color - Kolor dla guzika
		* @author Rafa� �wi�der
		*/
		void setPressColor(const sf::Color &color);


		/**
		* Ustawianie koloru tekstu dla spoczynku
		* /param color - Kolor dla guzika
		* @author Rafa� �wi�der
		*/
		void setIdleTextColor(const sf::Color &color);
		/**
		* Ustawianie koloru tekstu dla najechania kursorem
		* /param color - Kolor dla guzika
		* @author Rafa� �wi�der
		*/
		void setHoverTextColor(const sf::Color &color);
		/**
		* Ustawianie koloru tekstu dla wci�ni�cia
		* /param color - Kolor dla guzika
		* @author Rafa� �wi�der
		*/
		void setPressTextColor(const sf::Color &color);



		/**
		* Pobranie informacji o aktywno�ci guzika
		* @return Prawda je�eli aktywny i fa�sz je�eli nieaktywny
		* @author Rafa� �wi�der
		*/
		bool getState() { return _active; };
		/**
		* Pobranie rozmiaru guzika
		* @return Rozmiar guzika w wektorze @D
		* @author Rafa� �wi�der
		*/
		const sf::Vector2f &getSize() {	return shape.getSize();	}
		/**
		* Pobranie tekstury guzika
		* @return Wska�nik do tekstury guzika
		* @author Rafa� �wi�der
		*/
		const sf::Texture *getTexture() { return shape.getTexture(); }
		/**
		* Pobranie rozmiar�w i pozycji fragmentu tekstury wy�wietlanej na guziku
		* @return Rozmiaary prostok�ta jako fragment wy�wietlanej tekstury
		* @author Rafa� �wi�der
		*/
		const sf::IntRect &getTextureRect() { return shape.getTextureRect(); }
		/**
		* Pobranie pozycji guzika
		* @return Pozycja guzika w wektorze 2D
		* @author Rafa� �wi�der
		*/
		const sf::Vector2f &getPosition() { return shape.getPosition(); }
		/**
		* Pobranie pozycji i wymiar�w czworok�ta okre�laj�cego kolizj�
		* @return Prostok�t okre�laj�cy kolizj�
		* @author Rafa� �wi�der
		*/
		const sf::FloatRect &getShapeBounds() { return shape.getLocalBounds(); }



		/**
		* Pobranie informacji czy tekst jest wy�wietlany na guziku
		* @return Prawda je�eli wy�wietlany i fa�sz je�eli nie
		* @author Rafa� �wi�der
		*/
		bool isTextOn() const { return _text_on; }
		/**
		* Pobranie tekstu wy�wietlaj�cego si� na guziku
		* @return Tekst z guzika
		* @author Rafa� �wi�der
		*/
		const sf::String &getTextString() const { return text.getString(); }
		/**
		* Pobranie czcionki tekstu z guzika
		* @return Czcionka tekstu z guzika
		* @author Rafa� �wi�der
		*/
		const sf::Font &getTextFont() const { return *(text.getFont()); }
		/**
		* Pobranie rozmiaru tekstu guzika
		* @return Rozmiar tekstu z guzika
		* @author Rafa� �wi�der
		*/
		const unsigned int getTextCharSize() const { return text.getCharacterSize(); }
		/**
		* Pobranie rozmiaru odst�pu pomi�dzy liniami tekstu guzika
		* @return Rozmiar odst�pu mi�dzy liniami tekstu
		* @author Rafa� �wi�der
		*/
		float getTextLineSpacing() const { return text.getLineSpacing(); }
		/**
		* Pobranie rozmiaru odst�pu pomi�dzy literami tekstu guzika
		* @return Rozmiar odst�pu mi�dzy literami tekstu
		* @author Rafa� �wi�der
		*/
		float getTextLetterSpacing() const { return text.getLetterSpacing(); }
		/**
		* Pobranie stylu tekstu guzika
		* @return Styl tekstu guzika
		* @author Rafa� �wi�der
		*/
		const sf::Uint32 &getTextStyle() const { return text.getStyle(); }
		/**
		* Pobranie aktualnego koloru tekstu guzika
		* @return Aktualny kolor tekstu guzika
		* @author Rafa� �wi�der
		*/
		const sf::Color &getTextColor() const { return text.getFillColor(); }
		/**
		* Pobranie koloru obw�dki tekstu guzika
		* @return Kolor obw�dki tekstu guzika
		* @author Rafa� �wi�der
		*/
		const sf::Color &getTextOutlineColor() const { return text.getOutlineColor(); }
		/**
		* Pobranie pozycji tekstu z guzika
		* @return Pozycja tekstu guzika w wektorze 2D
		* @author Rafa� �wi�der
		*/
		const sf::Vector2f &getTextPosition() const { return text.getPosition(); }
		/**
		* Pobranie grubo�ci obw�dki tekstu guzika
		* @return Grubo�� obw�dki tekstu guzika
		* @author Rafa� �wi�der
		*/
		float getTextOutlineThickness() const { return text.getOutlineThickness(); }
		/**
		* Pobranie czworok�ta od kolizji tekstu guzika
		* @return Pozycja i rozmiar prostok�ta kolizyjnego tekstu guzika
		* @author Rafa� �wi�der
		*/
		const sf::FloatRect &getTextBounds() const { return text.getLocalBounds(); }



		/**
		* Pobranie koloru guzika dla spoczynku
		* @return Kolor guzika w stanie spoczynku
		* @author Rafa� �wi�der
		*/
		const sf::Color &getIdleColor() const { return _idle_color; }
		/**
		* Pobranie koloru guzika dla najechania
		* @return Kolor guzika po najechaniu kursorem
		* @author Rafa� �wi�der
		*/
		const sf::Color &getHoverColor() const { return _hover_color; }
		/**
		* Pobranie koloru guzika po jego wci�ni�ciu
		* @return Kolor guzika po jego wci�ni�ciu
		* @author Rafa� �wi�der
		*/
		const sf::Color &getPressColor() const { return _press_color; }


		/**
		* Pobranie koloru tekstu guzika dla spoczynku
		* @return Kolor tekstu guzika w stanie spoczynku
		* @author Rafa� �wi�der
		*/
		const sf::Color &getIdleTextColor() const { return _idle_text_color; }
		/**
		* Pobranie koloru tekstu guzika dla najechania
		* @return Kolor tekstu guzika po najechaniu kursorem
		* @author Rafa� �wi�der
		*/
		const sf::Color &getHoverTextColor() const { return _hover_text_color; }
		/**
		* Pobranie koloru tekstu guzika po jego wci�ni�ciu
		* @return Kolor tekstu guzika po jego wci�ni�ciu
		* @author Rafa� �wi�der
		*/
		const sf::Color &getPressTextColor() const { return _press_text_color; }

		

		/**
		* Konstruktor domy�lny guzika
		* @author Rafa� �wi�der
		*/
		Button() : Button(sf::Vector2f(200, 100), sf::Vector2f(0, 0)) {};
		/**
		* Konstruktor domy�lny guzika
		* /param size - Rozmiar guzika w wektorze 2D
		* /param position - Pozycja guzika w oknie w wektorze 2D
		* /param activated - Stan aktywno�ci guzika
		* /param text_on - Wy�wietlanie tekstu guzika
		* @author Rafa� �wi�der
		*/
		Button(const sf::Vector2f& size, const sf::Vector2f& position, bool activated = true, bool text_on = true);
		

		/**
		* Obs�uga funkcjonalno�ci guzika
		* /param win - Okno programu
		* @author Rafa� �wi�der
		*/
		void update(sf::RenderWindow &win);
		/**
		* Sprawdzenie najechania kursorem na guzik
		* @return Prawda je�eli najechano kursorem, fa�sz je�eli nie
		* @author Rafa� �wi�der
		*/
		bool hovered() { return _hovered; }
		/**
		* Sprawdzenie przytrzymania guzika
		* @return Prawda je�eli wci�nieto guzik, fa�sz je�eli nie
		* @author Rafa� �wi�der
		*/
		bool held() { return _held; }
		/**
		* Sprawdzenie klikni�cia guzika
		* @return Prawda je�eli klikni�to guzik, fa�sz je�eli nie
		* @author Rafa� �wi�der
		*/
		bool clicked() { return _clicked; }
	};
}

#endif