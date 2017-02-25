#include <iostream>
#include <iomanip>
#include <fstream>

#include "Gameplay.h"

game::Map** game::createMap(int sizeOfMapHeight, int sizeOfMapWidth, char* levelName)
{
	game::Map** map = new game::Map*[sizeOfMapHeight];
	for (int i = 0; i < sizeOfMapHeight; i++)
	{
		map[i] = new game::Map[sizeOfMapWidth];
	}

	char currentSymbol;
	std::ifstream fin(levelName, std::ios_base::in);

	for (int i = 0; i < sizeOfMapHeight; i++)
	{
		for (int j = 0; j < sizeOfMapWidth; j++)
		{
			currentSymbol = fin.get();
			if (currentSymbol == NEW_LINE)
				currentSymbol = fin.get();

			switch (currentSymbol)
			{
			case HERO_SYMBOL:
				map[i][j].type = HERO;
				map[i][j].hero.xCoordinate = i;
				map[i][j].hero.yCoordinate = j;
				break;
			case BLOCK_SHARP:
				map[i][j].type = BLOCK;
				map[i][j].block.xCoordinate = i;
				map[i][j].block.yCoordinate = j;
				break;
			case EMPTY_SPACE:
				map[i][j].type = EMPTY_SPACE;
				map[i][j].emptySpace.xCoordinate = i;
				map[i][j].emptySpace.yCoordinate = j;
				break;
			default:
				break;
			}
		}
	}
	fin.close();

	return map;
}

void game::drawFrame(int sizeOfMapHeight, int sizeOfMapWidth, game::Map** map)
{
	for (int i = 0; i < sizeOfMapHeight; i++)
	{
		for (int j = 0; j < sizeOfMapWidth; j++)
		{
			switch (map[i][j].type)
			{
			case HERO:
				std::cout << HERO;
				break;
			case BLOCK:
				std::cout << BLOCK;
				break;
			case EMPTY_SPACE:
				std::cout << EMPTY_SPACE;
				break;
			}
		}
		std::cout << std::endl;
	}
}

