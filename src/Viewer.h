#ifndef VIEWER_H
#define VIEWER_H
#include <SFML/Graphics.hpp>
#include "Block.h"
#include "mapCLASS.h"
class Viewer
{
	sf::RenderWindow *window;
	mapCLASS *map;
public:
	Block *block;
	Viewer(Block *block, mapCLASS *map, RenderWindow *window)
	{
		this->block = block;
		this->map = map;
		this->window = window;
	}

	void mapDraw()
	{
		RectangleShape shape;
		shape.setSize(Vector2f(20, 20));
		shape.setOrigin(Vector2f(0, 0));
		shape.setOutlineThickness(1);
		shape.setOutlineColor(Color::Black);
		for (int i = 0; i < map->getMatrixSize().x; i++)
			for (int j = 0; j < map->getMatrixSize().y; j++)
			{
				switch (map->getColor(i,j))
				{
				case 0:shape.setFillColor(Color::Black); break;
				case 1:shape.setFillColor(Color::Red); break;
				case 2:shape.setFillColor(Color::Blue); break;
				case 3:shape.setFillColor(Color::Green); break;
				case 4:shape.setFillColor(Color::White); break;
				case 5:shape.setFillColor(Color::Cyan); break;
				case 6:shape.setFillColor(Color::Magenta); break;
				}
				shape.setPosition(Vector2f(20 * j, 20 * i));
				window->draw(shape);
			}
	}

	void blockDraw()
	{
		RectangleShape shape;
		shape.setSize(Vector2f(20, 20));
		shape.setOrigin(Vector2f(0, 0));
		shape.setOutlineThickness(1);
		shape.setOutlineColor(Color::Black);
		switch (block->color_)
			{
			case 0:shape.setFillColor(Color::Black); break;
			case 1:shape.setFillColor(Color::Red); break;
			case 2:shape.setFillColor(Color::Blue); break;
			case 3:shape.setFillColor(Color::Green); break;
			case 4:shape.setFillColor(Color::White); break;
			case 5:shape.setFillColor(Color::Cyan); break;
			case 6:shape.setFillColor(Color::Magenta); break;
			}
		for (int i = 0; i < block->N; i++)
		{
			shape.setPosition(Vector2f(20 * block->parts[i].X, 20 * block->parts[i].Y));
			window->draw(shape);
		}
	}
};
#endif
