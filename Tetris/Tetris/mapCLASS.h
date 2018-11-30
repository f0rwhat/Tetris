#ifndef MAPCLASS_H
#define MAPCLASS_H
#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <windows.h>
#include "blockCLASS.h"

const int N = 21, M = 12;

class mapCLASS
{
	int map[N][M];
	sf::RenderWindow *window;
	blockCLASS *block;
public:
	mapCLASS(sf::RenderWindow *window)
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
		newblock();
	}
	
	int blockErase()
	{
		for (int i = 0; i < block->N; i++)
			map[block->parts[i].Y][block->parts[i].X] = 0;
		return 0;
	}

	int blockAdd()
	{
		for (int i = 0; i < block->N; i++)
			map[block->parts[i].Y][block->parts[i].X] = block->color;
		return 0;
	}

	int blockTurn()
	{
		blockErase();
		block->turn(map);
		blockAdd();
		return 0;
	}

	int newblock()
	{
		srand((unsigned)time(NULL));
		if (block != NULL)
		{
			delete[] block->parts;
			delete(block);
		}
		block = new blockCLASS(rand()%4+1,map);
		for(int i=0;i<block->N;i++)
			if (map[block->parts[i].Y][block->parts[i].X] != 0) {over(); return 0; }
		blockAdd();
		return 0;
	}

	int blockMove(sf::Keyboard::Key key)
	{
		bool check = true;
		switch (key)
		{
		case sf::Keyboard::Left: 
			for (int i = 0; i < block->N; i++)
				if (block->parts[i].incheckLeft && (!(map[block->parts[i].Y][block->parts[i].X - 1] == 0) || block->parts[i].X == 0)) check = false; 
			break;
		case sf::Keyboard::Right: 
			for (int i = 0; i < block->N; i++)
				if (block->parts[i].incheckRight && (!(map[block->parts[i].Y][block->parts[i].X + 1] == 0) || block->parts[i].X == M-1)) check = false; 
			break;
		}
		if (check) 
		{
			blockErase();
			block->move(key);
			blockAdd();
		}
		return 0;
	}

	int over()
	{
		ShowWindow(FindWindowA("ConsoleWindowClass", NULL), 1);
		std::cout << "Game Over" << std::endl;
		delete[] block->parts;
		delete[] block; 
		window->close(); 
		return 0;
	}

	int shift()
	{
		if (block == NULL || block->parts == NULL) return 0;
		for (int i = 0; i < block->N; i++)
			if (block->parts[i].incheckDown && !(map[block->parts[i].Y + 1][block->parts[i].X] == 0))
				if (block->parts[i].Y == 0) { over(); return 0; }
				else { stack(); newblock(); return 0; }
		blockErase();
		block->move(sf::Keyboard::Down);
		blockAdd();
		return 0;
	}

	int draw()
	{
		sf::RectangleShape shape;
		shape.setSize(sf::Vector2f(20, 20));
		shape.setOrigin(sf::Vector2f(0, 0));
		shape.setOutlineThickness(1);
		shape.setOutlineColor(sf::Color::Black);
		for (int i = 0; i < N-1; i++)
			for (int j = 1; j < M-1; j++)
			{
				switch (map[i][j])
				{
					case 0:shape.setFillColor(sf::Color::Black); break;
					case 1:shape.setFillColor(sf::Color::Red); break;
					case 2:shape.setFillColor(sf::Color::Blue); break;
					case 3:shape.setFillColor(sf::Color::Green); break;
					case 4:shape.setFillColor(sf::Color::White); break;
					case 5:shape.setFillColor(sf::Color::Cyan); break;
					case 6:shape.setFillColor(sf::Color::Magenta); break;
				}
				shape.setPosition(sf::Vector2f(20 * j-20, 20 * i));
				window->draw(shape);
			}
		return 0;
	}

	int stack()
	{
		for (int i = N - 2; i > 0; i--)
		{
			bool check = true;
			for (int j = 1; j < M-1; j++)
				if (map[i][j] == 0) check = false;
			if (check)
			{
				for (int z = i; z > 0; z--)
					for (int j = 1; j < M-1; j++)
						map[z][j] = map[z - 1][j];
				i++;
			}
		}
		return 0;
	}

};
#endif
