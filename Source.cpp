#include <conio.h>
#include <iostream>
#include "Field.h"

int main()
{
	Field f;

	Game g(f);

	g.start();

	_getch();
	return 0;
}