// #include "Platform/Platform.hpp"
#include <bits/stdc++.h>

#include "Platform/Platform.hpp"
#include "draw/draw.hpp"
using namespace sf;

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

int main() {
  RenderWindow window(VideoMode(900, 500), "SFML-Tutorial", Style::Close);
  window.setFramerateLimit(60);

  RectangleShape line, win;

  Vector2i posStart = Vector2i(-1, -1), posEnd = Vector2i(-1, -1);
  Vector2i winStart = Vector2i(-1, -1), winEnd = Vector2i(-1, -1);

  while (window.isOpen()) {
    Event event;
    while (window.pollEvent(event)) {
      // int flag = 0;
      if (event.type == Event::EventType::Closed) {
        window.close();
      }
      if (Mouse::isButtonPressed(Mouse::Left)) {
        if (posStart.x == -1) {
          // flag = 1;
          posStart = Mouse::getPosition(window);
        } else if (posEnd.x == -1) {
          posEnd = Mouse::getPosition(window);
          line = getLine(posStart, posEnd);
        } else if (winStart.x == -1) {
          winStart = Mouse::getPosition(window);
        } else if (winEnd.x == -1) {
          winEnd = Mouse::getPosition(window);
          win = getWindow(winStart, winEnd);
        } else {
          // thuc hien xen tia
          posStart = Vector2i(-1, -1);
          posEnd = Vector2i(-1, -1);
          winStart = Vector2i(-1, -1);
          winEnd = Vector2i(-1, -1);
          // flag = 0;
        }
      }
    }
    window.clear();
    if (posEnd.x != -1) window.draw(line);
    if (winEnd.x != -1) window.draw(win);
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