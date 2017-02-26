#include "Gameplay.h"
#include "Map.h"

game::Map** game::createMap(char* levelName)
{
	game::Map** map = new game::Map*[MAP_HEIGHT];
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		map[i] = new game::Map[MAP_WIDTH];
	}

	char currentSymbol;
	std::ifstream fin(levelName, std::ios_base::in);

	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			currentSymbol = fin.get();
			if (currentSymbol == NEW_LINE)
				currentSymbol = fin.get();

			switch (currentSymbol)
			{
			case HERO_SYMBOL:
				map[i][j].type = HERO;
				map[i][j].xCoordinate = j;
				map[i][j].yCoordinate = i;
				map[i][j].passable = true;
				break;
			case BLOCK_SHARP:
				map[i][j].type = BLOCK;
				map[i][j].xCoordinate = j;
				map[i][j].yCoordinate = i;
				map[i][j].passable = false;
				break;
			case EMPTY_SPACE:
				map[i][j].type = EMPTY_SPACE;
				map[i][j].xCoordinate = j;
				map[i][j].yCoordinate = i;
				map[i][j].passable = true;
				break;
			case AIM_DOT:
				map[i][j].type = AIM_DOT;
				map[i][j].xCoordinate = j;
				map[i][j].yCoordinate = i;
				map[i][j].passable = true;
				break;
			default:
				break;
			}
		}
	}
	fin.close();

	return map;
}
