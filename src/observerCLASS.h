#ifndef OBSERVER_H
#define OBSERVER_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include "blockCLASS.h"
#include "mapCLASS.h"

using namespace sf;
const int standart = 250, speed = 25;

class observerCLASS
{
	RenderWindow *window;
	blockCLASS *block;
	mapCLASS *map;
	float timelimiter = standart;
public:

	observerCLASS(blockCLASS *block, mapCLASS *map, RenderWindow *window)
	{
		this->block = block;
		this->map = map;
		this->window = window;
	}

	void gameStart()
	{
		ShowWindow(FindWindowA("ConsoleWindowClass", NULL), 0);
		block->newblock();
		blockDraw();
	}

	void gameOver()
	{
		ShowWindow(FindWindowA("ConsoleWindowClass", NULL), 1);
		std::cout << "Game Over" << std::endl;
		window->close();
	}

	void blockErase()
	{
		for (int i = 0; i < block->N; i++)
			map->map[block->parts[i].Y][block->parts[i].X] = 0;
		
	}

	void blockDraw()
	{
		for (int i = 0; i < block->N; i++)
			map->map[block->parts[i].Y][block->parts[i].X] = block->color;
	}

	int checkOver()
	{
		for (int i = 0; i < block->N; i++)
			if (block->parts[i].incheckDown && !(map->map[block->parts[i].Y + 1][block->parts[i].X] == 0))
				if (block->parts[i].Y == 0) return 1; 
		return 0;
	}

	void mapshift()
	{
		if (block->parts != NULL)
		{
			blockErase();
			if (!block->move(Keyboard::Down))
				if (checkOver()) gameOver();
				else
				{
					blockDraw();
					mapstack();
					block->newblock();
					blockDraw();
				}
			else blockDraw();
		}
	}

	void mapstack()
	{
		for (int i = N - 2; i > 0; i--)
		{
			bool check = true;
			for (int j = 1; j < M - 1; j++)
				if (map->map[i][j] == 0) check = false;
			if (check)
			{
				for (int z = i; z > 0; z--)
					for (int j = 1; j < M - 1; j++)
						map->map[z][j] = map->map[z - 1][j];
				i++;
			}
		}
	}

	void keycheck(Keyboard::Key key, float currenttime)
	{
		switch (key)
		{
		case Keyboard::Down:
			timelimiter = speed;
			break;
		case Keyboard::Left:
			if (timecheck(currenttime)) 
			{ 
				blockErase();
				block->move(Keyboard::Left); 
				blockDraw();
			}
			break;
		case Keyboard::Right:
			if (timecheck(currenttime))
			{
				blockErase();
				block->move(Keyboard::Right);
				blockDraw();
			}
			break;
		case Keyboard::Up:
			if (timecheck(currenttime))
			{
				blockErase();
				block->turn();
				blockDraw();
			}
			break;
		}
	}

	int timecheck(float currenttime)
	{
		if (timelimiter < currenttime) return 1;
		timelimiter = standart;
		return 0;
	}
};

#endif