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
		font.loadFromFile("D:\\Tetris\\arial.ttf");
		text.setString(_text);
		text.setFont(font);
		text.setCharacterSize(size);
		text.setFillColor(Color::Red);
		text.setPosition(x, y);
	}

	void display(RenderWindow& window) {
		window.draw(text);
	}
};
