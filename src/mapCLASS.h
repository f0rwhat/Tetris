#ifndef MAPCLASS_H
#define MAPCLASS_H
#include <SFML/Graphics.hpp>

using namespace sf;

class mapCLASS
{
	RenderWindow *window;
	int N = 20, M = 10;
	int **map;

public:
	mapCLASS(RenderWindow *window)
	{
		map = new int*[N];
		for (int i = 0; i < N; i++)
		{
			map[i] = new int[M];
			for (int j = 0; j < M ; j++)
				map[i][j] = 0;
		}
		this->window = window;
	}

	int filled(int j, int i)
	{
		if (j < 0 || j >= M || i < 0 || i >= N) return 1;
		if (map[i][j] == 0) return 0;
		return 1;
	}

	void fill(int j, int i, int color)
	{
		map[i][j] = color;
	}

	int getColor(int i, int j)
	{
		return map[i][j];
	}

	Vector2i getMatrixSize()
	{
		return Vector2i(N, M);
	}

	void mapstack()
	{
		for (int i = N - 1; i > 0; i--)
		{
			bool check = true;
			for (int j = 1; j < M - 1; j++)
				if (map[i][j] == 0) check = false;
			if (check)
			{
				for (int z = i; z > 0; z--)
					for (int j = 1; j < M - 1; j++)
						map[z][j] = map[z - 1][j];
				i++;
			}
		}
	}
};
#endif
