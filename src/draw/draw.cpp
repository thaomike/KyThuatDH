#include "draw.hpp"

double convertRadianToDegree(double radian) {
  double pi = 3.14159;
  return (radian * (180 / pi));
}

double calculateAngle(sf::Vector2i a, sf::Vector2i b) {
  double tanAlpha = (double)(b.y - a.y) / (b.x - a.x);
  return convertRadianToDegree(atan(tanAlpha));
}

double length(sf::Vector2i a, sf::Vector2i b) {
  double x = abs(a.x - b.x);
  double y = abs(a.y - b.y);
  return sqrt(x * x + y * y);
}

sf::RectangleShape getLine(sf::Vector2i a, sf::Vector2i b) {
  sf::RectangleShape line;
  line.setPosition(sf::Vector2f(a.x, a.y));
  if (b.x - a.x < 0)
    line.setRotation(calculateAngle(a, b) + 180);
  else
    line.setRotation(calculateAngle(a, b));
  line.setSize(sf::Vector2f(length(a, b), 1));
  return line;
}

sf::RectangleShape getWindow(sf::Vector2i a, sf::Vector2i b) {
  sf::RectangleShape win;
  win.setFillColor(sf::Color::Transparent);
  win.setOutlineColor(sf::Color::Yellow);
  win.setOutlineThickness(1);
  win.setPosition(sf::Vector2f(a.x, a.y));
  win.setSize(sf::Vector2f(b.x - a.x, b.y - a.y));
  return win;
}