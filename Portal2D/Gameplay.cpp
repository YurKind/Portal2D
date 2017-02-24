#include "Gameplay.h"
#include <iostream>
#include <iomanip>


game::Map** game::createMap(int sizeOfMapHeight, int sizeOfMapWidth)
{
	game::Map** map = new game::Map*[sizeOfMapHeight];
	for (int i = 0; i < sizeOfMapHeight; i++)
	{
		map[i] = new game::Map[sizeOfMapWidth];
	}
	return map;
}

