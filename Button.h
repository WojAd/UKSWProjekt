#ifndef BUTTON_H
#define BUTTON_H

/** \file Button.h
 * Plik naglowkowy dla klasy przycisku klikanego myszk¹.
 */

#include <SFML/Graphics.hpp>

namespace qiwi
{
	/**
	* Klasa reprezentujaca przycisk klikany myszk¹
	* @author Rafa³ Œwi¹der
	*/
	class Button : public sf::Drawable
	{
	private:		
		bool _active;/**< Aktywnoœæ guzika*/
		bool _text_on;/**< Wyœwietlanie tekstu na guziku*/
		/**
		* Dopasowanie pozycji tekstu w guziku
		* @author Rafa³ Œwi¹der
		*/
		void adjust_text_position();

		bool _hovered;/**< Najechano kursorem*/
		bool _held;/**< Wciœniêto przycisk*/
		bool _clicked;/**< Klikniêto guzik*/
		/**
		* Namierzenie guzika kursorem
		* /param win - okno programu
		* @return Prawda - je¿eli namierzono, a w przeciwnym wypadku fa³sz
		* @author Rafa³ Œwi¹der
		*/
		bool aimed(sf::RenderWindow &win);

		sf::Color _idle_color;/**< Kolor guzika w spoczynku*/
		sf::Color _hover_color;/**< Kolor guzika po najechaniu*/
		sf::Color _press_color;/**< Kolor guzika przy wciœniêciu*/

		sf::Color _idle_text_color;/**< Kolor tekstu guzika w spoczynku*/
		sf::Color _hover_text_color;/**< Kolor tekstu guzika po najechaniu*/
		sf::Color _press_text_color;/**< Kolor tekstu guzika przy wciœniêciu*/

		sf::RectangleShape shape;/**< Kszta³t guzika do wyrysowania w oknie*/
		sf::Text text;/**< Tekst wyœwietlany na guziku*/

	protected:
		/**
		* Rysowanie guzika
		* /param target - okno, w którym guzik ma zostaæ wyrysowany
		* /param states - dodatkowe opcje rysowania
		* @author Rafa³ Œwi¹der
		*/
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	public:
		/**
		* Ustawienie aktywnoœci guzika
		* /param activated - prawda:guzik aktywny, fa³sz:nieaktywny
		* @author Rafa³ Œwi¹der
		*/
		void setState(bool activated);
		/**
		* Rozmiar guzika
		* /param size - Wektor 2D z wymiarami dla guzika
		* @author Rafa³ Œwi¹der
		*/
		void setSize(const sf::Vector2f &size);
		/**
		* Rozmiar guzika
		* /param x - Szerokoœæ guzika
		* /param y - Wysokoœæ guzika
		* @author Rafa³ Œwi¹der
		*/
		void setSize(float x, float y);
		/**
		* Tekstura guzika
		* /param texture - Tekstura guzika
		* /param resetRect - Wyœwietlanie ca³oœci tekstury
		* @author Rafa³ Œwi¹der
		*/
		void setTexture(const sf::Texture &texture, bool resetRect = false);
		/**
		* Fragment tekstury guzika
		* /param rect - Po³o¿enie i wymiary fragmentu tekstury do wyœwietlenia
		* @author Rafa³ Œwi¹der
		*/
		void setTextureRect(const sf::IntRect &rect);
		/**
		* Ustawianie pozycji guzika
		* /param x - Szerokoœæ
		* /param y - Wysokoœæ
		* @author Rafa³ Œwi¹der
		*/
		void setPosition(float x, float y);
		/**
		* Ustawianie pozycji guzika
		* /param position - Wektor 2D z koordynatami pozycji dla guzika
		* @author Rafa³ Œwi¹der
		*/
		void setPosition(const sf::Vector2f &position);
		/**
		* Przemieszczenie guzika
		* /param offsetX - Przemieszczenie w osi X
		* /param offsetY - Przemieszczenie w osi Y
		* @author Rafa³ Œwi¹der
		*/
		void move(float offsetX, float offsetY);
		/**
		* Przemieszczenie guzika
		* /param offset - Wektor 2D o jaki ma siê przemieœciæ guzik
		* @author Rafa³ Œwi¹der
		*/
		void move(const sf::Vector2f &offset);
		/**
		* Ustawianie koloru guzika
		* /param color - Kolor dla guzika
		* @author Rafa³ Œwi¹der
		*/
		void setColor(const sf::Color &color);

		/**
		* Wyœwietlanie tekstu na guziku
		* /param text_on - W³¹czenie tekstu
		* /param font - Czcionka dla tekstu na guziku
		* @author Rafa³ Œwi¹der
		*/
		void setTextOn(bool text_on = false,sf::Font *font = nullptr);
		/**
		* Zmiana tekstu na guziku
		* /param str - Tekst dla guzika
		* @author Rafa³ Œwi¹der
		*/
		void setTextString(const sf::String &str);
		/**
		* Ustawianie czcionki dla tekstu guzika
		* /param font - Czcionka dla guzika
		* @author Rafa³ Œwi¹der
		*/
		void setTextFont(const sf::Font &font);
		/**
		* Ustawianie rozmiaru tekstu guzika
		* /param size - Rozmiar tekstu
		* @author Rafa³ Œwi¹der
		*/
		void setTextCharSize(unsigned int size);
		/**
		* Ustawianie odstêpu pomiêdzy liniami tekstu
		* /param spacingFactor - Wielkoœæ odstêpu
		* @author Rafa³ Œwi¹der
		*/
		void setTextLineSpacing(float spacingFactor);
		/**
		* Ustawianie odstêpu pomiêdzy literami tekstu
		* /param spacingFactor - Wielkoœæ odstêpu
		* @author Rafa³ Œwi¹der
		*/
		void setTextLetterSpacing(float spacingFactor);
		/**
		* Ustawianie stylu dla tekstu
		* /param style - Styl dla tekstu
		* @author Rafa³ Œwi¹der
		*/
		void setTextStyle(sf::Uint32 style);
		/**
		* Ustawianie koloru dla tekstu na guziku
		* /param color - Kolor dla tekstu guzika
		* @author Rafa³ Œwi¹der
		*/
		void setTextColor(const sf::Color &color);
		/**
		* Ustawianie koloru obwódki tekstu
		* /param color - Kolor dla obwódki
		* @author Rafa³ Œwi¹der
		*/
		void setTextOutlineColor(const sf::Color &color);
		/**
		* Ustawianie gruboœci obwódki tekstu
		* /param thickness - Gruboœæ obwódki
		* @author Rafa³ Œwi¹der
		*/
		void setTextOutlineThickness(float thickness);


		/**
		* Ustawianie koloru guzika dla spoczynku
		* /param color - Kolor dla guzika
		* @author Rafa³ Œwi¹der
		*/
		void setIdleColor(const sf::Color &color);
		/**
		* Ustawianie koloru guzika dla najechania kursorem
		* /param color - Kolor dla guzika
		* @author Rafa³ Œwi¹der
		*/
		void setHoverColor(const sf::Color &color);
		/**
		* Ustawianie koloru guzika dla wciœniêcia
		* /param color - Kolor dla guzika
		* @author Rafa³ Œwi¹der
		*/
		void setPressColor(const sf::Color &color);


		/**
		* Ustawianie koloru tekstu dla spoczynku
		* /param color - Kolor dla guzika
		* @author Rafa³ Œwi¹der
		*/
		void setIdleTextColor(const sf::Color &color);
		/**
		* Ustawianie koloru tekstu dla najechania kursorem
		* /param color - Kolor dla guzika
		* @author Rafa³ Œwi¹der
		*/
		void setHoverTextColor(const sf::Color &color);
		/**
		* Ustawianie koloru tekstu dla wciœniêcia
		* /param color - Kolor dla guzika
		* @author Rafa³ Œwi¹der
		*/
		void setPressTextColor(const sf::Color &color);



		/**
		* Pobranie informacji o aktywnoœci guzika
		* @return Prawda je¿eli aktywny i fa³sz je¿eli nieaktywny
		* @author Rafa³ Œwi¹der
		*/
		bool getState() { return _active; };
		/**
		* Pobranie rozmiaru guzika
		* @return Rozmiar guzika w wektorze @D
		* @author Rafa³ Œwi¹der
		*/
		const sf::Vector2f &getSize() {	return shape.getSize();	}
		/**
		* Pobranie tekstury guzika
		* @return WskaŸnik do tekstury guzika
		* @author Rafa³ Œwi¹der
		*/
		const sf::Texture *getTexture() { return shape.getTexture(); }
		/**
		* Pobranie rozmiarów i pozycji fragmentu tekstury wyœwietlanej na guziku
		* @return Rozmiaary prostok¹ta jako fragment wyœwietlanej tekstury
		* @author Rafa³ Œwi¹der
		*/
		const sf::IntRect &getTextureRect() { return shape.getTextureRect(); }
		/**
		* Pobranie pozycji guzika
		* @return Pozycja guzika w wektorze 2D
		* @author Rafa³ Œwi¹der
		*/
		const sf::Vector2f &getPosition() { return shape.getPosition(); }
		/**
		* Pobranie pozycji i wymiarów czworok¹ta okreœlaj¹cego kolizjê
		* @return Prostok¹t okreœlaj¹cy kolizjê
		* @author Rafa³ Œwi¹der
		*/
		const sf::FloatRect &getShapeBounds() { return shape.getLocalBounds(); }



		/**
		* Pobranie informacji czy tekst jest wyœwietlany na guziku
		* @return Prawda je¿eli wyœwietlany i fa³sz je¿eli nie
		* @author Rafa³ Œwi¹der
		*/
		bool isTextOn() const { return _text_on; }
		/**
		* Pobranie tekstu wyœwietlaj¹cego siê na guziku
		* @return Tekst z guzika
		* @author Rafa³ Œwi¹der
		*/
		const sf::String &getTextString() const { return text.getString(); }
		/**
		* Pobranie czcionki tekstu z guzika
		* @return Czcionka tekstu z guzika
		* @author Rafa³ Œwi¹der
		*/
		const sf::Font &getTextFont() const { return *(text.getFont()); }
		/**
		* Pobranie rozmiaru tekstu guzika
		* @return Rozmiar tekstu z guzika
		* @author Rafa³ Œwi¹der
		*/
		const unsigned int getTextCharSize() const { return text.getCharacterSize(); }
		/**
		* Pobranie rozmiaru odstêpu pomiêdzy liniami tekstu guzika
		* @return Rozmiar odstêpu miêdzy liniami tekstu
		* @author Rafa³ Œwi¹der
		*/
		float getTextLineSpacing() const { return text.getLineSpacing(); }
		/**
		* Pobranie rozmiaru odstêpu pomiêdzy literami tekstu guzika
		* @return Rozmiar odstêpu miêdzy literami tekstu
		* @author Rafa³ Œwi¹der
		*/
		float getTextLetterSpacing() const { return text.getLetterSpacing(); }
		/**
		* Pobranie stylu tekstu guzika
		* @return Styl tekstu guzika
		* @author Rafa³ Œwi¹der
		*/
		const sf::Uint32 &getTextStyle() const { return text.getStyle(); }
		/**
		* Pobranie aktualnego koloru tekstu guzika
		* @return Aktualny kolor tekstu guzika
		* @author Rafa³ Œwi¹der
		*/
		const sf::Color &getTextColor() const { return text.getFillColor(); }
		/**
		* Pobranie koloru obwódki tekstu guzika
		* @return Kolor obwódki tekstu guzika
		* @author Rafa³ Œwi¹der
		*/
		const sf::Color &getTextOutlineColor() const { return text.getOutlineColor(); }
		/**
		* Pobranie pozycji tekstu z guzika
		* @return Pozycja tekstu guzika w wektorze 2D
		* @author Rafa³ Œwi¹der
		*/
		const sf::Vector2f &getTextPosition() const { return text.getPosition(); }
		/**
		* Pobranie gruboœci obwódki tekstu guzika
		* @return Gruboœæ obwódki tekstu guzika
		* @author Rafa³ Œwi¹der
		*/
		float getTextOutlineThickness() const { return text.getOutlineThickness(); }
		/**
		* Pobranie czworok¹ta od kolizji tekstu guzika
		* @return Pozycja i rozmiar prostok¹ta kolizyjnego tekstu guzika
		* @author Rafa³ Œwi¹der
		*/
		const sf::FloatRect &getTextBounds() const { return text.getLocalBounds(); }



		/**
		* Pobranie koloru guzika dla spoczynku
		* @return Kolor guzika w stanie spoczynku
		* @author Rafa³ Œwi¹der
		*/
		const sf::Color &getIdleColor() const { return _idle_color; }
		/**
		* Pobranie koloru guzika dla najechania
		* @return Kolor guzika po najechaniu kursorem
		* @author Rafa³ Œwi¹der
		*/
		const sf::Color &getHoverColor() const { return _hover_color; }
		/**
		* Pobranie koloru guzika po jego wciœniêciu
		* @return Kolor guzika po jego wciœniêciu
		* @author Rafa³ Œwi¹der
		*/
		const sf::Color &getPressColor() const { return _press_color; }


		/**
		* Pobranie koloru tekstu guzika dla spoczynku
		* @return Kolor tekstu guzika w stanie spoczynku
		* @author Rafa³ Œwi¹der
		*/
		const sf::Color &getIdleTextColor() const { return _idle_text_color; }
		/**
		* Pobranie koloru tekstu guzika dla najechania
		* @return Kolor tekstu guzika po najechaniu kursorem
		* @author Rafa³ Œwi¹der
		*/
		const sf::Color &getHoverTextColor() const { return _hover_text_color; }
		/**
		* Pobranie koloru tekstu guzika po jego wciœniêciu
		* @return Kolor tekstu guzika po jego wciœniêciu
		* @author Rafa³ Œwi¹der
		*/
		const sf::Color &getPressTextColor() const { return _press_text_color; }

		

		/**
		* Konstruktor domyœlny guzika
		* @author Rafa³ Œwi¹der
		*/
		Button() : Button(sf::Vector2f(200, 100), sf::Vector2f(0, 0)) {};
		/**
		* Konstruktor domyœlny guzika
		* /param size - Rozmiar guzika w wektorze 2D
		* /param position - Pozycja guzika w oknie w wektorze 2D
		* /param activated - Stan aktywnoœci guzika
		* /param text_on - Wyœwietlanie tekstu guzika
		* @author Rafa³ Œwi¹der
		*/
		Button(const sf::Vector2f& size, const sf::Vector2f& position, bool activated = true, bool text_on = true);
		

		/**
		* Obs³uga funkcjonalnoœci guzika
		* /param win - Okno programu
		* @author Rafa³ Œwi¹der
		*/
		void update(sf::RenderWindow &win);
		/**
		* Sprawdzenie najechania kursorem na guzik
		* @return Prawda je¿eli najechano kursorem, fa³sz je¿eli nie
		* @author Rafa³ Œwi¹der
		*/
		bool hovered() { return _hovered; }
		/**
		* Sprawdzenie przytrzymania guzika
		* @return Prawda je¿eli wciœnieto guzik, fa³sz je¿eli nie
		* @author Rafa³ Œwi¹der
		*/
		bool held() { return _held; }
		/**
		* Sprawdzenie klikniêcia guzika
		* @return Prawda je¿eli klikniêto guzik, fa³sz je¿eli nie
		* @author Rafa³ Œwi¹der
		*/
		bool clicked() { return _clicked; }
	};
}

#endif