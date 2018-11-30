#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "mapCLASS.h"
#include <Windows.h>

const int standart = 250, speed = 25;

int main()
{
	ShowWindow(FindWindowA("ConsoleWindowClass", NULL), 0);
	sf::RenderWindow window(sf::VideoMode(200, 400), "Tetris");
	sf::Event event;
	int timecheck = standart;
	window.setVerticalSyncEnabled(true);

	mapCLASS map(&window);
	while (window.isOpen())
	{
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) map.over();
	
		window.clear();

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down) timecheck = speed;
		else timecheck = standart;
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left) map.blockMove(sf::Keyboard::Left);
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) map.blockMove(sf::Keyboard::Right);
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) map.blockTurn();

		map.shift();
		map.draw();
		window.display();
		Sleep(timecheck);
	}
	system("pause");
	return 0;
}