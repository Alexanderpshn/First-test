#ifndef FIELD_H
#define FIELD_H
#include <vector>

class Coordinates {
public:
	int x;
	int y;

	bool operator==(const Coordinates &) const;
	bool operator!=(const Coordinates &obj) const { return !((*this) == obj); }
};


class Snake {
public:
	enum Position { UP, DOWN, RIGHT, LEFT };

	Coordinates head;
	/*Coordinates eat;*/
	Position pos;

	int len = 1;

	void operator++();
	

	std::vector<Coordinates> dots;
	std::vector<Coordinates> eat;
};

class Field {
private:
	static const int height = 23;
	static const int lenght = height * 2;
	
	char Board[height][lenght];

	Snake snake;
	Coordinates element;

	//���������� ������� ������ �� �����
	bool change_snake_coordinates();

	void change_snake_tail(Coordinates);
	void change_element();
public:
	Field();

	//������� �� ���� ������������: ����� ��������� ������
	bool change_position(char);

	//����� �� ��� �������, �������� � ������� �����������
	void move();

	void draw() const;

	bool game_status() const;
	int snake_length() { return snake.len; }
};


class Game {
private:
	Field &f;

public:
	Game(Field &_f) : f(_f) {};
	void start();
};
#endif // !FIELD_H
