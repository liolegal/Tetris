
#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

class Label {
private:
	double x;
	double y;
	Text text;
	Font font;
public:
	Label(double x, double y, string _text, int size = 20) {
		this->x = x; this->y = y;
		font.loadFromFile("COOPBL.ttf");
		text.setString(_text);
		text.setFont(font);
		text.setCharacterSize(size);
		text.setFillColor(Color::Black);
		text.setPosition(x, y);
	}

	void display(RenderWindow& window) {
		window.draw(text);
	}

	void changeText(string s) {
		text.setString(s);
	}
	void changeColor(Color color) {
		text.setFillColor(color);
	}
};
