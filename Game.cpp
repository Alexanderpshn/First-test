#include "Field.h"
#include <iostream>
#include <ctime>
#include <conio.h>
#include <locale>

void Game::start()
{
	for (int i = 0; i < 23 * 3; i++) std::cout << '*';
	std::cout << "\n               Hello, this is my first Snake game\n";
	std::cout << "                    Press any key for start\n";
	for (int i = 0; i < 23 * 3; i++) std::cout << '*';
	std::cout << std::endl << std::endl;

	_getch();

	char ch;

	clock_t timer;

	while (f.game_status())
	{
		timer = clock() + CLOCKS_PER_SEC / 3;
		while (clock() < timer) {};
		f.draw();

		ch = _getch();
		f.change_position(ch);

		f.move();
	}


	std::cout << std::endl << std::endl;
	for (int i = 0; i < 23 * 3; i++) std::cout << '*';
	std::cout << "\n                    Your final score is: "<< f.snake_length() << std::endl;
	for (int i = 0; i < 23 * 3; i++) std::cout << '*';

	std::cout << "Do you want to start new Game?(Y or N): ";

}