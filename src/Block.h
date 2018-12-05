#ifndef BLOCKCLASS_H
#define BLOCKCLASS_H

#include <SFML/Graphics.hpp>
#include <time.h>
#include "mapCLASS.h"

using namespace sf;
const int Nm = 20, Mm = 10;
class Block
{
protected:
    struct Part
	{
		int X, Y;
	};
public:	
    Part *parts = nullptr;
    static constexpr int N = 4;
    int type_, color_, side_;

	void newBlock()
	{
		srand((unsigned)time(NULL));
		color_ = rand() % 6 + 1;
		type_ = rand() % 4 + 1;
		side_ = 2;
		if (parts != nullptr) delete[] parts;
		switch (type_)
		{
		case 1:
			parts = buildLine();
			break;
		case 2:
			parts = buildSqaure();
			break;
		case 3:
			parts = buildZigZag();
			break;
		case 4:
			parts = buildZigZagLeft();
			break;
		}
	}
	Part *buildLine()
	{
		parts = new Part[N];
		for (int i = 0, j = Mm / 2 - 2; i < N; i++, j++)
		{
			parts[i].Y = 0;
			parts[i].X = j;						//0 1 2 3
		}
		return parts;
	}
	Part *buildSqaure()
	{
		parts = new Part[N];
		parts[0].Y = 0; parts[0].X = Mm / 2;
		parts[1].Y = 0; parts[1].X = Mm / 2 + 1;			//0 1
		parts[2].Y = 1; parts[2].X = Mm / 2;				//2 3
		parts[3].Y = 1; parts[3].X = Mm / 2 + 1;
		return parts;
	}
	Part *buildZigZag()
	{
		parts = new Part[N];
		parts[0].Y = 0; parts[0].X = Mm / 2 - 1;
		parts[1].Y = 0; parts[1].X = Mm / 2;			//0 1
		parts[2].Y = 1; parts[2].X = Mm / 2;			//  2 3
		parts[3].Y = 1; parts[3].X = Mm / 2 + 1;
		return parts;
	}
	Part *buildZigZagLeft()
	{
		parts = new Part[N];
		parts[0].Y = 0; parts[0].X = Mm / 2 + 1;
		parts[1].Y = 0; parts[1].X = Mm / 2;			//   1 0
		parts[2].Y = 1; parts[2].X = Mm / 2;			// 3 2
		parts[3].Y = 1; parts[3].X = Mm / 2 - 1;
		return parts;
	}

	void turnLine(mapCLASS *map)
	{
		bool check = true;
		switch (side_)
		{
		case 1:
			if (parts[0].Y < Nm - 4)
			{
				for (int i = parts[0].Y, j = parts[0].X; i <= parts[0].Y + 3; i++)
					if (map->filled(j, i)!=0)
						check = false;
			}
			else check = false;
			if (check)
			{
				for (int i = 1; i < N; i++)
				{
					parts[i].X = parts[0].X;
					parts[i].Y = parts[0].Y + i;
				}
				side_ = 2;
			}
			break;
		case 2:
			if (parts[0].X < Mm - 4)
			{
				for (int j = parts[0].X, i = parts[0].Y; j <= parts[0].X + 3; j++)
					if (map->filled(j, i))
						check = false;
			}
			else check = false;
			if (check)
			{
				for (int i = 1; i < N; i++)
				{
					parts[i].Y = parts[0].Y;
					parts[i].X = parts[0].X + i;
				}
				side_ = 1;
			}
			break;
		}
	}
	void turnZigZag(mapCLASS *map)
	{
		bool check = true;
		switch (side_)
		{
		case 1:
			if (!(parts[0].Y < Nm - 3)) check = false;
			if (map->filled(parts[0].X, parts[0].Y + 1) != 0) check = false;
			if (map->filled(parts[0].X - 1, parts[0].Y + 1) != 0) check = false;
			if (map->filled(parts[0].X, parts[0].Y + 2) != 0) check = false;
			if (check)
			{
				parts[1].X = parts[0].X;
				parts[1].Y = parts[0].Y + 1;
				parts[2].X = parts[0].X - 1;
				parts[2].Y = parts[0].Y + 1;
				parts[3].X = parts[0].X - 1;
				parts[3].Y = parts[0].Y + 2;
				side_ = 2;
			}
			break;
		case 2:
			if (!(parts[0].X < Mm - 3)) check = false;
			if (map->filled(parts[0].X + 1, parts[0].Y) != 0) check = false;
			if (map->filled(parts[0].X + 1, parts[0].Y + 1) != 0) check = false;
			if (map->filled(parts[0].X + 2, parts[0].Y + 1) != 0) check = false;
			if (check)
			{
				parts[1].X = parts[0].X + 1;
				parts[1].Y = parts[0].Y;
				parts[2].X = parts[0].X + 1;
				parts[2].Y = parts[0].Y + 1;
				parts[3].X = parts[0].X + 2;
				parts[3].Y = parts[0].Y + 1;
				side_ = 1;
			}
			break;
		}
	}
	void turnZigZagLeft(mapCLASS *map)
	{
		bool check = true;
		switch (side_)
		{
		case 1:
			if (!(parts[0].Y < Nm - 3)) check = false;
			if (map->filled(parts[0].X, parts[0].Y + 1) != 0) check = false;
			if (map->filled(parts[0].X + 1, parts[0].Y + 1) != 0) check = false;
			if (map->filled(parts[0].X + 1, parts[0].Y + 2) != 0) check = false;
			if (check)
			{
				parts[1].X = parts[0].X;
				parts[1].Y = parts[0].Y + 1;
				parts[2].X = parts[0].X + 1;
				parts[2].Y = parts[0].Y + 1;
				parts[3].X = parts[0].X + 1;
				parts[3].Y = parts[0].Y + 2;
				side_ = 2;
			}
			break;
		case 2:
			if (!(parts[0].X > 2)) check = false;
			if (map->filled(parts[0].X - 1, parts[0].Y) != 0) check = false;
			if (map->filled(parts[0].X - 1, parts[0].Y + 1) != 0) check = false;
			if (map->filled(parts[0].X - 2, parts[0].Y + 1) != 0) check = false;
			if (check)
			{
				parts[1].X = parts[0].X - 1;
				parts[1].Y = parts[0].Y;
				parts[2].X = parts[0].X - 1;
				parts[2].Y = parts[0].Y + 1;
				parts[3].X = parts[0].X - 2;
				parts[3].Y = parts[0].Y + 1;
				side_ = 1;
			}
			break;
		}
	}
	
	int move(Keyboard::Key key, mapCLASS *map)
	{
		switch (key)
		{
		case Keyboard::Down:
			for (int i = 0; i < N; i++)
				if (map->filled(parts[i].X, parts[i].Y + 1))
					return 0;
			for (int i = 0; i < N; i++)
				parts[i].Y++;
			break;
		case Keyboard::Left:
			for (int i = 0; i < N; i++)
				if (map->filled(parts[i].X - 1, parts[i].Y))
					return 0;
			for (int i = 0; i < N; i++)
				parts[i].X--;
			break;
		case Keyboard::Right:
			for (int i = 0; i < N; i++)
				if (map->filled(parts[i].X + 1, parts[i].Y))
					return 0;
			for (int i = 0; i < N; i++)
				parts[i].X++;
			break;
		case Keyboard::Up:
			switch (type_)
			{
			case 1:turnLine(map); break;
			case 3:turnZigZag(map); break;
			case 4:turnZigZagLeft(map); break;
			}
			break;
		}
		return 1;
	}
};

#endif
