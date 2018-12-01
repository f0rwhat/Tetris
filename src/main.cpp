#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "mapCLASS.h"
#include "blockCLASS.h"
#include "observerCLASS.h"
using namespace sf;

int main()
{
	RenderWindow window(sf::VideoMode(200, 400), "Tetris");
	window.setVerticalSyncEnabled(true);
	Event event;
	Clock clock;
	
	mapCLASS map(&window);
	blockCLASS block(&map);
	observerCLASS observer(&block, &map, &window);
	
	clock.restart();
	observer.gameStart();
	while (window.isOpen())
	{
		while (window.pollEvent(event))
			if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)) { observer.gameOver(); break; }
	
		
		if (event.type == Event::KeyPressed) observer.keycheck(event.key.code, clock.getElapsedTime().asMilliseconds());
		if (observer.timecheck(clock.getElapsedTime().asMilliseconds()))
		{
			observer.mapshift();
			clock.restart();

			window.clear();
			map.draw();
			window.display();
		}
	}
	
	system("pause");
	return 0;
}