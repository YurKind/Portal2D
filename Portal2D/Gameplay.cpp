#include "Gameplay.h"
#include <iostream>
#include <iomanip>


game::Map** game::createMap()
{
	game::Map** map = new game::Map*[5];
	for (int i = 0; i < 5; i++)
	{
		map[i] = new game::Map[5];
	}
	return map;
}

