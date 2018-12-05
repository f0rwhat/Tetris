#ifndef OBSERVER_H
#define OBSERVER_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Block.h"
#include "mapCLASS.h"
#include "Viewer.h"

using namespace sf;
const int standart = 250, speed = 25;

class observerCLASS
{
	RenderWindow *window;
	Block *block;
	mapCLASS *map;
	Viewer *viewer;
	float timelimiter = standart;
public:

	observerCLASS(Block *block, mapCLASS *map, RenderWindow *window, Viewer *viewer)
	{
		this->block = block;
		this->map = map;
		this->window = window;
		this->viewer = viewer;
	}

	void gameStart()
	{
		block->newBlock();
	}

	void gameOver()
	{
		std::cout << "Game Over" << std::endl;
		window->close();
	}

	int checkOver()
	{
		for (int i = 0; i < block->N; i++)
			if (map->filled(block->parts[i].X, block->parts[i].Y + 1))
				if (block->parts[i].Y == 0) return 1; 
		return 0;
	}

	void shift()
	{
		if (!block->move(Keyboard::Down, map))
		{
			for (int i = 0; i < block->N; i++)
				map->fill(block->parts[i].X, block->parts[i].Y, block->color_);
			if (!checkOver())
			{
				map->mapstack();
				block->newBlock();
			}
			else gameOver();
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
		case Keyboard::Right:
		case Keyboard::Up:
			if (timecheck(currenttime)) 
			{ 
				block->move(key, map); 
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
