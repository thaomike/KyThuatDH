// #include "Platform/Platform.hpp"
#include "Platform/Platform.hpp"
#include <bits/stdc++.h>
using namespace sf;

double Length(Vector2i a, Vector2i b);

double Length(Vector2i a, Vector2i b)
{
	double x = abs(a.x - b.x);
	double y = abs(a.y - b.y);

	return sqrt(x * x + y * y);
}

// khi chạy:
/*
click lần 1: set tọa độ đầu tiên của đoạn thẳng
click lần 2: set tọa độ điểm thứ 2
-> sau khi click lần 2 thì đoạn thẳng hiện ra
click lần 3: set tọa độ điểm 1 của cửa sổ
lần 4: tọa độ 2 của cửa sổ
-> cửa sổ hiện ra
click 5: reset
*/

int main()
{
	RenderWindow window(sf::VideoMode(900, 500), "SFML-Tutorial", sf::Style::Close);
	window.setFramerateLimit(60);

	sf::RectangleShape line;
	RectangleShape win;
	win.setFillColor(Color::Transparent);
	win.setOutlineColor(Color::Yellow);
	win.setOutlineThickness(1);

	sf::Vector2i posStart = Vector2i(-1, -1), posEnd = Vector2i(-1, -1);
	sf::Vector2i winStart = Vector2i(-1, -1), winEnd = Vector2i(-1, -1);

	posStart = Vector2i(-1, -1);
	posEnd = Vector2i(-1, -1);
	winStart = Vector2i(-1, -1);
	winEnd = Vector2i(-1, -1);
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			// int flag = 0;
			if (event.type == sf::Event::EventType::Closed)
			{
				window.close();
			}
			if (Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (posStart.x == -1)
				{
					// flag = 1;
					posStart = sf::Mouse::getPosition(window);
					line.setPosition(Vector2f(posStart.x, posStart.y));
				}
				else if (posEnd.x == -1)
				{
					posEnd = sf::Mouse::getPosition(window);
					line.setSize(Vector2f(Length(posStart, posEnd), 1));
				}
				else if (winStart.x == -1)
				{
					winStart = sf::Mouse::getPosition(window);
					win.setPosition(Vector2f(winStart.x, winStart.y));
				}
				else if (winEnd.x == -1)
				{
					winEnd = Mouse::getPosition(window);
					win.setSize(Vector2f(winEnd.x - winStart.x, winEnd.y - winStart.y));
				}
				else
				{
					//thuc hien xen tia
					posStart = Vector2i(-1, -1);
					posEnd = Vector2i(-1, -1);
					winStart = Vector2i(-1, -1);
					winEnd = Vector2i(-1, -1);
					// flag = 0;
				}
				// Vector2i p = Mouse::ge
			}
		}

		window.clear();
		if (posEnd.x != -1)
			window.draw(line);
		if (winEnd.x != -1)
			window.draw(win);
		// window.draw(text);
		window.display();
	}

	return 0;
}

/*
Text text;
	std::stringstream ss;
	ss << posStart.x;

	std::string s;
	ss >> s;
	// text.setFont(Font::); // font is a sf::Font

	// set the string to display
	text.setString("Hello world");

	// set the character size
	text.setCharacterSize(24); // in pixels, not points!

	// set the color
	text.setFillColor(sf::Color::Red);

	// set the text style
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);
	// text.setString(s);
	text.setCharacterSize(24);
	// text.setString(s);
*/