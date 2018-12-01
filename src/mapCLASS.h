#ifndef MAPCLASS_H
#define MAPCLASS_H
#include <SFML/Graphics.hpp>
using namespace sf;
const int N = 21, M = 12;

class mapCLASS
{
	RenderWindow *window;
public:
	int map[N][M];

	mapCLASS(RenderWindow *window)
	{
		for (int i = 0; i < N-1; i++)
			for (int j = 1; j < M-1; j++)
				map[i][j] = 0;
		for (int i = 0; i < N; i++)
		{
			map[i][0] = -1;
			map[i][M - 1] = -1;
		}
		for (int j = 0; j < M; j++)
			map[N - 1][j] = -1;
		this->window = window;
	}

	void draw()
	{
		RectangleShape shape;
		shape.setSize(Vector2f(20, 20));
		shape.setOrigin(Vector2f(0, 0));
		shape.setOutlineThickness(1);
		shape.setOutlineColor(Color::Black);
		for (int i = 0; i < N-1; i++)
			for (int j = 1; j < M-1; j++)
			{
				switch (map[i][j])
				{
					case 0:shape.setFillColor(Color::Black); break;
					case 1:shape.setFillColor(Color::Red); break;
					case 2:shape.setFillColor(Color::Blue); break;
					case 3:shape.setFillColor(Color::Green); break;
					case 4:shape.setFillColor(Color::White); break;
					case 5:shape.setFillColor(Color::Cyan); break;
					case 6:shape.setFillColor(Color::Magenta); break;
				}
				shape.setPosition(Vector2f(20 * j-20, 20 * i));
				window->draw(shape);
			}
	}

};
#endif
