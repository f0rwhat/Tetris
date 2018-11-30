#ifndef BLOCKCLASS_H
#define BLOCKClASS_H
#include <SFML/Graphics.hpp>
#include <time.h>

const int Nm = 21, Mm = 12;
class blockCLASS
{
	struct partsSTRUCT
	{
		int X, Y;
		bool incheckDown, incheckLeft, incheckRight;
	};
	int side;
public:
	int N = 4;
	int type, color;
	partsSTRUCT *parts=NULL;

	blockCLASS(int type,int map[Nm][Mm])
	{
		srand((unsigned)time(NULL));
		color = rand() % 6 + 1;
		parts = new partsSTRUCT[N];
		switch (type)
		{
		case 1:
			for (int i = 0; i < N; i++)
				parts[i].Y = 0;
			for (int i = 0, j = Mm / 2 - 2; i < N; i++, j++)
				parts[i].X = j;
			for (int i = 0; i < N; i++)
			{
				parts[i].incheckDown = true;
				parts[i].incheckLeft = false;   //0 1 2 3
				parts[i].incheckRight = false;
			}
			parts[0].incheckLeft = true;
			parts[3].incheckRight = true;
			break;
		case 2:
			parts[0].Y = 0; parts[0].X = Mm / 2;
			parts[1].Y = 0; parts[1].X = Mm / 2 + 1;			//0 1
			parts[2].Y = 1; parts[2].X = Mm / 2;				//2 3
			parts[3].Y = 1; parts[3].X = Mm / 2 + 1;
			parts[0].incheckDown = false;
			parts[0].incheckLeft = true;
			parts[0].incheckRight = false;
			parts[1].incheckDown = false;
			parts[1].incheckLeft = false;
			parts[1].incheckRight = true;
			parts[2].incheckDown = true;
			parts[2].incheckLeft = true;
			parts[2].incheckRight = false;
			parts[3].incheckDown = true;
			parts[3].incheckLeft = false;
			parts[3].incheckRight = true;
			break;
		case 3:
			parts[0].Y = 0; parts[0].X = Mm / 2 - 1;
			parts[1].Y = 0; parts[1].X = Mm / 2 ;			//0 1
			parts[2].Y = 1; parts[2].X = Mm / 2;			//  2 3
			parts[3].Y = 1; parts[3].X = Mm / 2 + 1;
			parts[0].incheckDown = true;
			parts[0].incheckLeft = true;
			parts[0].incheckRight = false;
			parts[1].incheckDown = false;
			parts[1].incheckLeft = false;
			parts[1].incheckRight = true;
			parts[2].incheckDown = true;
			parts[2].incheckLeft = true;
			parts[2].incheckRight = false;
			parts[3].incheckDown = true;
			parts[3].incheckLeft = false;
			parts[3].incheckRight = true;
			break;
		case 4:
			parts[0].Y = 0; parts[0].X = Mm / 2 + 1;
			parts[1].Y = 0; parts[1].X = Mm / 2;			//   1 0
			parts[2].Y = 1; parts[2].X = Mm / 2;			// 3 2
			parts[3].Y = 1; parts[3].X = Mm / 2 - 1;
			parts[0].incheckDown = true;
			parts[0].incheckLeft = false;
			parts[0].incheckRight = true;
			parts[1].incheckDown = false;
			parts[1].incheckLeft = true;
			parts[1].incheckRight = false;
			parts[2].incheckDown = true;
			parts[2].incheckLeft = false;
			parts[2].incheckRight = true;
			parts[3].incheckDown = true;
			parts[3].incheckLeft = true;
			parts[3].incheckRight = false;
			break;
		}
		this->type = type;
		side = 1;
	}
	
	int move(sf::Keyboard::Key key)
	{
		switch (key)
		{
		case sf::Keyboard::Down:
			for (int i = 0; i < N; i++)
				parts[i].Y++;
			break;
		case sf::Keyboard::Left:
			for (int i = 0; i < N; i++)
				parts[i].X--;
			break;
		case sf::Keyboard::Right:
			for (int i = 0; i < N; i++)
				parts[i].X++;
			break;
		}
		return 0;
	}

	int turn(int map[Nm][Mm])
	{
		bool check = true;
		switch (type)
		{
		case 1:
			switch (side)
			{
			case 1:
				if (parts[0].Y < Nm - 4)
				{
					for (int i = parts[0].Y, j = parts[0].X; i <= parts[0].Y + 3; i++)
						if (map[i][j] != 0) check = false;
				}
				else check = false;
				if (check)
				{
					for (int i = 1; i < N; i++)
					{
						parts[i].X = parts[0].X;
						parts[i].Y = parts[0].Y + i;
					}
					for (int i = 0; i < N; i++)
					{
						parts[i].incheckDown = false;
						parts[i].incheckLeft = true;
						parts[i].incheckRight = true;
					}
					parts[3].incheckDown = true;
					side = 2;
				}
				break;
			case 2: 
				if (parts[0].X < Mm - 4)
				{
					for (int j = parts[0].X, i = parts[0].Y; j <= parts[0].X + 3; j++)
						if (map[i][j] != 0) check = false;
				}
				else check = false;
				if (check)
				{
					for (int i = 1; i < N; i++)
					{
						parts[i].Y = parts[0].Y;
						parts[i].X = parts[0].X + i;
					}
					for (int i = 0; i < N; i++)
					{
						parts[i].incheckDown = true;
						parts[i].incheckLeft = false;
						parts[i].incheckRight = false;
					}
					parts[0].incheckLeft = true;
					parts[3].incheckRight = true;
					side = 1;
				}
				break;
			}
			break;
		case 3:
			switch (side)
			{
			case 1:
				
				if (map[parts[0].X][parts[0].Y + 1] != 0) check = false;
				if (map[parts[0].X - 1][parts[0].Y + 1] != 0) check = false;
				if (map[parts[0].X - 1][parts[0].Y + 2] != 0) check = false;
				
				if (check)
				{
					parts[1].X = parts[0].X;
					parts[1].Y = parts[0].Y + 1;
					parts[2].X = parts[0].X - 1;
					parts[2].Y = parts[0].Y + 1;
					parts[3].X = parts[0].X -1;
					parts[3].Y = parts[0].Y + 2;
			
					parts[0].incheckDown = false;
					parts[0].incheckLeft = true;
					parts[0].incheckRight = true;
					parts[1].incheckDown = true;
					parts[1].incheckLeft = false;
					parts[1].incheckRight = true;
					parts[2].incheckDown = false;
					parts[2].incheckLeft = true;
					parts[2].incheckRight = false;
					parts[3].incheckDown = true;
					parts[3].incheckLeft = true;
					parts[3].incheckRight = true;
					
					side = 2;
				}
				break;
			case 2:
				if (map[parts[0].X + 1][parts[0].Y] != 0) check = false;
				if (map[parts[0].X + 1][parts[0].Y + 1] != 0) check = false;
				if (map[parts[0].X + 2][parts[0].Y + 1] != 0) check = false;
				if (check)
				{
					parts[1].X = parts[0].X + 1;
					parts[1].Y = parts[0].Y;
					parts[2].X = parts[0].X + 1;
					parts[2].Y = parts[0].Y + 1;
					parts[3].X = parts[0].X + 2;
					parts[3].Y = parts[0].Y + 1;

					parts[0].incheckDown = true;
					parts[0].incheckLeft = true;
					parts[0].incheckRight = false;
					parts[1].incheckDown = false;
					parts[1].incheckLeft = false;
					parts[1].incheckRight = true;
					parts[2].incheckDown = true;
					parts[2].incheckLeft = true;
					parts[2].incheckRight = false;
					parts[3].incheckDown = true;
					parts[3].incheckLeft = false;
					parts[3].incheckRight = true;
					side = 1;
				}
				break;
			}
			break;
		case 4:
			switch (side)
			{
			case 1:

				if (map[parts[0].X][parts[0].Y + 1] != 0) check = false;
				if (map[parts[0].X + 1][parts[0].Y + 1] != 0) check = false;
				if (map[parts[0].X + 1][parts[0].Y + 2] != 0) check = false;
				if (check)
				{
					parts[1].X = parts[0].X;
					parts[1].Y = parts[0].Y + 1;
					parts[2].X = parts[0].X + 1;
					parts[2].Y = parts[0].Y + 1;
					parts[3].X = parts[0].X + 1;
					parts[3].Y = parts[0].Y + 2;

					parts[0].incheckDown = false;
					parts[0].incheckLeft = true;
					parts[0].incheckRight = true;
					parts[1].incheckDown = true;
					parts[1].incheckLeft = true;
					parts[1].incheckRight = false;
					parts[2].incheckDown = false;
					parts[2].incheckLeft = false;
					parts[2].incheckRight = true;
					parts[3].incheckDown = true;
					parts[3].incheckLeft = true;
					parts[3].incheckRight = true;

					side = 2;
				}
				break;
			case 2:
				if (map[parts[0].X - 1][parts[0].Y] != 0) check = false;
				if (map[parts[0].X - 1][parts[0].Y + 1] != 0) check = false;
				if (map[parts[0].X - 2][parts[0].Y + 1] != 0) check = false;
				if (check)
				{
					parts[1].X = parts[0].X - 1;
					parts[1].Y = parts[0].Y;
					parts[2].X = parts[0].X - 1;
					parts[2].Y = parts[0].Y + 1;
					parts[3].X = parts[0].X - 2;
					parts[3].Y = parts[0].Y + 1;
					parts[0].incheckDown = true;
					parts[0].incheckLeft = false;
					parts[0].incheckRight = true;
					parts[1].incheckDown = false;
					parts[1].incheckLeft = true;
					parts[1].incheckRight = false;
					parts[2].incheckDown = true;
					parts[2].incheckLeft = false;
					parts[2].incheckRight = true;
					parts[3].incheckDown = true;
					parts[3].incheckLeft = true;
					parts[3].incheckRight = false;
					side = 1;
				}
				break;
			}
			break;
		}
		return 0;
	}
};
#endif

