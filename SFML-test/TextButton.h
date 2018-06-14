#ifndef TEXT_BUTTON_H
#define TEXT_BUTTON_H

#include <SFML/Graphics.hpp>

class TextButton {
public:
	TextButton() : TextButton("test", 40, sf::Color::White, 0, 0) {
	}
	TextButton(sf::String string, int fontSize, sf::Color fontColor, float x, float y) {
		if (!font.loadFromFile("font/contb.ttf"))//http://www.dafont.com/continuum.font
		{
			std::cerr << "Could not find contb.ttf font." << std::endl;
		}

		text.setFont(font); // font is a sf::Font
		text.setString(string);	// set the string to display
		text.setCharacterSize(fontSize); // set the character size in pixels, not points!
		text.setFillColor(fontColor);	// set the color
		text.setStyle(sf::Text::Bold); // set the text style
		text.setPosition(x, y);
	}
	TextButton(const TextButton& other) {
		if (this != &other) {
			text = other.text;
			font = other.font;
			text.setFont(font);
		}
	}
	bool contains(int x, int y) {
		return text.getGlobalBounds().contains((float)x, (float)y);
	}
	void setTextColor(sf::Color color) {
		text.setFillColor(color);
	}
	sf::Text getText() {
		return text;
	}
	
private:
	sf::Font font;
	sf::Text text;
};
#endif // !TEXT_BUTTON_H
