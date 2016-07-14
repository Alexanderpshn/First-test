#include "Field.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

bool Coordinates::operator==(const Coordinates &obj) const
{
	return (x == obj.x && y == obj.y);
}

Field::Field()
{
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < lenght; j++) {
			if (i == 0 || j == 0 || i == (height - 1) || j == (lenght - 1)) Board[i][j] = 'x';
			else Board[i][j] = ' ';
		}
	}
	snake.head.x = height / 2;
	snake.head.y = lenght / 2;

	//Изначально голова направлена вправо
	snake.pos = Snake::RIGHT;

	/*snake.save_pos.push_back(Snake::Line() = { snake.tail, snake.pos });*/
	/*Board[snake.head.x][snake.head.y] = '>';*/
	change_snake_coordinates();
	change_element();
}

void Field::draw() const
{
	system("cls");
	/*std::cout << std::endl << std::endl;*/
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < lenght; j++) {
			std::cout << Board[i][j];
		}
		std::cout << std::endl;
	}
}

void Field::change_element()
{
	//Рандомим позицию элемента
	//Проверяем занята ли позиция
	srand(time(NULL));
	do {
		element.x = rand() % (height - 1) + 1;
		element.y = rand() % (lenght + 1) + 1;
	} while (Board[element.x][element.y] != ' ');

	Board[element.x][element.y] = '@';
}

bool Field::change_position(char button)
{
	//Необходимо условие что направление меняется 
	//только если ячейка в которую меняется направление не занята
	switch (button)
	{
	case 'w':
	case 'W':
		if (snake.pos != Snake::DOWN) {
			snake.pos = Snake::UP;
		}
		break;

	case 's':
	case 'S':
		if (snake.pos != Snake::UP) {
			snake.pos = Snake::DOWN;
		}
		break;

	case 'a':
	case 'A':
		if (snake.pos != Snake::RIGHT) {
			snake.pos = Snake::LEFT;
		}
		break;

	case 'd':
	case 'D':
		if (snake.pos != Snake::LEFT) {
			snake.pos = Snake::RIGHT;
		}
		break;

	default:
		break;
	}

	return false;
}


bool Field::game_status() const
{
	if (Board[snake.head.x][snake.head.y] == 'x' || Board[snake.head.x][snake.head.y] == 'o') return false;
	else return true;
}

bool Field::change_snake_coordinates()
{
	if (game_status()) {
		if (snake.pos == Snake::UP) Board[snake.head.x][snake.head.y] = '^';
		else if (snake.pos == Snake::DOWN) Board[snake.head.x][snake.head.y] = 'v';
		else if (snake.pos == Snake::RIGHT) Board[snake.head.x][snake.head.y] = '>';
		else if (snake.pos == Snake::LEFT) Board[snake.head.x][snake.head.y] = '<';
		return true;
	}
	return false;
}

void Field::move()
{
	Coordinates prev = { snake.head.x, snake.head.y };

	switch (snake.pos)
	{
	case Snake::UP:
		snake.head.x--;
		break;
	case Snake::DOWN:
		snake.head.x++;
		break;
	case Snake::LEFT:
		snake.head.y--;
		break;
	case Snake::RIGHT:
		snake.head.y++;
		break;
	}
	

	//Если подобрали еду то меняем положение еды
	if (Board[snake.head.x][snake.head.y] == '@') {
		//push_back в вектор eat позицию snake_head
		/*snake.eat = snake.head;*/
		snake.eat.push_back(snake.head);

		//Меняем позицию элемента еды
		change_element();

		change_snake_tail(prev);
		for (int i = 0; i < snake.dots.size(); i++) {
			Board[snake.dots[i].x][snake.dots[i].y] = 'o';
		}

		if (!(snake.dots.size())) {
			snake.dots.push_back(snake.head);

			//Заменить eat на вектор и делать pop
			//Если больше 1 то поменять и pop, если нет то обнулить
			/*snake.eat[0].x = 0;
			snake.eat[0].y = 0;*/
			snake.eat.pop_back();
		}
		++snake;
	}
	else {
		/*change_snake_coordinates();*/
		change_snake_tail(prev);
		for (int i = 0; i < snake.dots.size(); i++) {
			Board[snake.dots[i].x][snake.dots[i].y] = 'o';
		}
	}

	//Вставляем знак направления на новую позицию
	change_snake_coordinates();
}

//Увеличение счетчика длины змеи
void Snake::operator++()
{
	len++;
}

void Field::change_snake_tail(Coordinates previous)
{

	int size = snake.dots.size();

	//Стираем последнюю позицию и переназначаем точки
	if (size) {
		//Сравниваем с snake.eat[0]
		if (snake.eat.size() && snake.dots[size - 1] == snake.eat[0]) {
			Board[snake.dots[size - 1].x][snake.dots[size - 1].y] = ' ';

			for (int i = size - 1; i > 0; i--) {
				snake.dots[i] = snake.dots[i - 1];
			}

			snake.dots[0] = previous;

			snake.dots.push_back(snake.eat[0]);

			for (int i = 0; i < snake.eat.size() - 1; ++i) {
				snake.eat[i] = snake.eat[i + 1];
			}
			snake.eat.pop_back();

		}
		else {
			Board[snake.dots[size - 1].x][snake.dots[size - 1].y] = ' ';

			for (int i = size - 1; i > 0; i--) {
				snake.dots[i] = snake.dots[i - 1];
			}

			snake.dots[0] = previous;
		}
	}
	else {
		Board[previous.x][previous.y] = ' ';
	}

}