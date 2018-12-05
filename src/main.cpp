#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "mapCLASS.h"
#include "Block.h"
#include "observerCLASS.h"
#include "Viewer.h"
using namespace sf;

int main()
{
	RenderWindow window(sf::VideoMode(200, 400), "Tetris");
	window.setVerticalSyncEnabled(true);
	Event event;
	Clock clock;
	
	mapCLASS map(&window);
    //Block *block(map);
	Block block;
	Viewer viewer(&block, &map, &window);
    observerCLASS observer(&block, &map, &window, &viewer);
	
	observer.gameStart();
	clock.restart();
	while (window.isOpen())
	{
		while (window.pollEvent(event))
            if (event.type == Event::Closed ||
               (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
            {
                observer.gameOver();
                break;
            }
	
        if (event.type == Event::KeyPressed)
            observer.keycheck(event.key.code, clock.getElapsedTime().asMilliseconds());
		if (observer.timecheck(clock.getElapsedTime().asMilliseconds()))
		{
			observer.shift();
			clock.restart();

			window.clear();
			viewer.mapDraw();
			viewer.blockDraw();
			window.display();
		}
	}
	
	system("pause");
	return 0;
}
