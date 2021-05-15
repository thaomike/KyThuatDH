#include "Platform/Platform.hpp"
#include "draw/draw.hpp"
#include <bits/stdc++.h>
using namespace sf;

#define TRUE 1
#define FALSE 0
#define LEFT 1
#define RIGHT 2
#define TOP 4
#define BOTTOM 8

typedef struct
{
	//    int Left, Top, Right, Bottom;
	int x1, y1, x2, y2;
} RECt;

typedef int CODE;

#define Accept(a, b) (!(a | b))
#define Reject(a, b) (a & b)

void EnCode(Vector2i p, CODE& u, RECt rwin);
void SwapPoint(Vector2i& p1, Vector2i& p2, CODE& c1, CODE& c2);
int CohenSutherlandClipping(Vector2i P1, Vector2i P2, Vector2i& Q1, Vector2i& Q2, RECt rWin);

void EnCode(Vector2i p, CODE& c, RECt rWin)
{
	if (rWin.x1 > rWin.x2)
	{
		int tmp = rWin.x1;
		rWin.x1 = rWin.x2;
		rWin.x2 = tmp;
	}
	if (rWin.y1 > rWin.y2)
	{
		int tmp = rWin.y1;
		rWin.y1 = rWin.y2;
		rWin.y2 = tmp;
	}

	c = 0;
	if (p.x < rWin.x1)
		c |= LEFT;
	if (p.x > rWin.x2)
		c |= RIGHT;
	if (p.y > rWin.y2)
		c |= TOP;
	if (p.y < rWin.y1)
		c |= BOTTOM;
}

void SwapPoint(Vector2i& p1, Vector2i& p2, CODE& c1, CODE& c2)
{

	if (!c1) // Neu p1 nam hoan toan trong cua so
	{
		Vector2i p;
		p = p1;
		p1 = p2;
		p2 = p;

		CODE c;
		c = c1;
		c1 = c2;
		c2 = c;
	}
}

// Tra ve TRUE neu co cat cua so. Nguoc lai tra ve FALSE
int CohenSutherlandClipping(Vector2i P1, Vector2i P2, Vector2i& Q1, Vector2i& Q2, RECt rWin)
{
	int fStop = FALSE, fResult = FALSE;
	CODE c1, c2;

	while (!fStop)
	{
		EnCode(P1, c1, rWin);
		EnCode(P2, c2, rWin);

		// Neu duong thang nam hoan toan ben trong cua so
		if (Accept(c1, c2))
		{
			fStop = TRUE; // break
			fResult = TRUE;
		} // Accept

		else
		{
			// Neu duong thang nam hoan toan ben ngoai cua so
			if (Reject(c1, c2))
			{
				fStop = TRUE; // break
			}				  // Reject
			else			  // Xet truong hop duong thang co the cat cua so
			{
				SwapPoint(P1, P2, c1, c2);
				float m;

				//    if(P2.x!=P1.x)
				m = float(P2.y - P1.y) / (P2.x - P1.x);

				if (c1 & LEFT)
				{
					P1.y += (rWin.x1 - P1.x) * m;
					P1.x = rWin.x1;
				} // Left
				else
				{
					if (c1 & RIGHT)
					{
						P1.y += (rWin.x2 - P1.x) * m;
						P1.x = rWin.x2;
					} // Right
					else
					{
						if (c1 & TOP)
						{
							if (P2.x != P1.x)
								P1.x += (rWin.y2 - P1.y) / m;
							P1.y = rWin.y2;
						}	 // Top
						else // Bottom
						{
							if (P2.x != P1.x)
								P1.x += (rWin.y1 - P1.y) / m;
							P1.y = rWin.y1;
						} // Bottom
					}
				}
			} // Xet truong hop duong thang co the cat cua so
		}

	} //while
	  //
	Q1 = P1;
	Q2 = P2;
	//    cout<<Q1.x<<" "<<Q1.y<<endl;
	//            cout<<Q2.x<<" "<<Q2.y<<endl;
	return (fResult);
} //CohenSutherlandClipping

//keo tha de ve duong thẳng và cua so
// sau khi set up doan thang va cua so xong, nhan enter de thuc hien xen tia
// click chuot mot lan nua de clear man hinh
int main()
{
	RenderWindow window(VideoMode(900, 500), "SFML-Tutorial", Style::Close);
	window.setFramerateLimit(60);
	Vector2i Q1, Q2;
	RECt rWin;

	RectangleShape line, win;

	Vector2i posStart = Vector2i(-1, -1), posEnd = Vector2i(-1, -1);
	Vector2i winStart = Vector2i(-1, -1), winEnd = Vector2i(-1, -1);

	int flag = 1;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			// int flag = 0;
			if (event.type == Event::EventType::Closed)
			{
				window.close();
			}
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				if (posStart.x == -1 && flag == 1)
				{
					// flag = 1;
					posStart = Mouse::getPosition(window);
				}
				else if (flag == 1)
				{
					posEnd = Mouse::getPosition(window);
					line = getLine(posStart, posEnd);
				}
				else if (winStart.x == -1 && flag == 2)
				{
					winStart = Mouse::getPosition(window);
				}
				else if (flag == 2)
				{
					winEnd = Mouse::getPosition(window);
					win = getWindow(winStart, winEnd);
				}
				else
				{
					// thuc hien xen tia
					posStart = Vector2i(-1, -1);
					posEnd = Vector2i(-1, -1);
					winStart = Vector2i(-1, -1);
					winEnd = Vector2i(-1, -1);
					// flag = 0;
				}
			}
			if (event.type == Event::MouseButtonReleased)
			{
				if (flag < 3)
					flag++;
				else
					flag = 1;
			}

			if (Keyboard ::isKeyPressed(Keyboard::Enter))
			{

				int maxY, minY, maxX, minX;
				if (winEnd.y > winStart.y)
				{
					maxY = winEnd.y;
					minY = winStart.y;
				}
				else
				{
					minY = winEnd.y;
					maxY = winStart.y;
				}
				if (winEnd.x > winStart.x)
				{
					maxX = winEnd.x;
					minX = winStart.x;
				}
				else
				{
					minX = winEnd.x;
					maxX = winStart.x;
				}
				rWin.y1 = maxY;
				rWin.x1 = minX;
				rWin.x2 = maxX;
				rWin.y2 = minY;

				if (CohenSutherlandClipping(posStart, posEnd, Q1, Q2, rWin) == 0)
				{
					posStart = Vector2i(-1, -1);
					posEnd = Vector2i(-1, -1);
				}
				else
				{
					CohenSutherlandClipping(posStart, posEnd, Q1, Q2, rWin);
					posStart = Q1;
					posEnd = Q2;
					line = getLine(posStart, posEnd);
				}
			}
		}
		window.clear();
		if (posEnd.x != -1)
			window.draw(line);
		if (winEnd.x != -1)
			window.draw(win);
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