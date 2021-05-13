#ifndef _DRAW_HPP
#define _DRAW_HPP

#include <SFML/Graphics.hpp>
#include <cmath>

sf::RectangleShape getLine(sf::Vector2i a, sf::Vector2i b);
sf::RectangleShape getWindow(sf::Vector2i a, sf::Vector2i b);
double calculateAngle(sf::Vector2i a, sf::Vector2i b);
double length(sf::Vector2i a, sf::Vector2i b);
double convertRadianToDegree(double radian);

#endif