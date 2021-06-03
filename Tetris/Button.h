#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

class Button {
private:
	double width;
	double height;
	double x, y;
	Font font;
	Text text;
	RectangleShape box;
public:
	Button(double _x, double _y, string _text = "Кнопка", double _width = 120, double _height = 35, int size = 20)
	{
		x = _x;
		y = _y;
		width = _width;
		height = _height;
		font.loadFromFile("D:\\Tetris\\COOPBL.ttf");
		text.setString(_text);
		text.setFont(font);
		text.setCharacterSize(size);
		text.setFillColor(Color::Black);
		//text.setOrigin(Vector2f((x + width) / 2, (y + height) / 2));
		text.setPosition(x, y);

		box.setSize(Vector2f(width, height));
		box.setPosition(x, y);
		box.setOutlineThickness(2);
		box.setFillColor(Color::White);
		box.setOutlineColor(Color::Black);
	}
	//Проверка нажатия на кнопку
	bool select(Vector2i mouse)
	{
		if (box.getGlobalBounds().contains(mouse.x, mouse.y)) {
			return  true;
		}
		else {
			return false;
		}
	}

	void contain(Vector2i mouse) {
		if (box.getGlobalBounds().contains(mouse.x, mouse.y))
		{
			box.setFillColor(Color(133, 133, 133));
			box.setSize(Vector2f(width + 4, height + 4));
			box.setPosition(x - 2, y - 2);
		}
		else
		{
			box.setFillColor(Color::White);
			box.setSize(Vector2f(width, height));
			box.setPosition(x, y);
		}
	}

	void display(RenderWindow& window) {
		window.draw(box);
		window.draw(text);
	}
	void setText(string _text) {
		text.setString(_text);
	}
};
