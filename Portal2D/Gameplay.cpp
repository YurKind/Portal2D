#include <iostream>
#include <iomanip>
#include <fstream>
#include <conio.h>

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
				map[i][j].xCoordinate = i;
				map[i][j].yCoordinate = j;
				map[i][j].passable = true;
				break;
			case BLOCK_SHARP:
				map[i][j].type = BLOCK;
				map[i][j].xCoordinate = i;
				map[i][j].yCoordinate = j;
				map[i][j].passable = false;
				break;
			case EMPTY_SPACE:
				map[i][j].type = EMPTY_SPACE;
				map[i][j].xCoordinate = i;
				map[i][j].yCoordinate = j;
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

void game::drawFrame(int sizeOfMapHeight, int sizeOfMapWidth, game::Map** map)
{
	for (int i = 0; i < sizeOfMapWidth; i++)
	{
		for (int j = 0; j < sizeOfMapHeight; j++)
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

void game::moving(int heroXCoordinate, int heroYCoordinate, game::Map** map)
{
	while (true)
	{
		if (_kbhit())
		{
			switch (_getch())
			{
			case(A_LOWER_CASE /*|| A_UPPER_CASE*/) :
				int x = NULL;
				int y = NULL;
				for (int i = 0; i < MAP_HEIGHT; i++)
				{
					for (int j = 0; j < MAP_WIDTH; j++)
					{
						if (map[i][j].type == HERO)
						{
							x = i;
							y = j;
						}
					}
				}
				if (map[x - 1][y].passable == true)
				{
					map[x][y].type = EMPTY_SPACE;
					map[x - 1][y].type = HERO;
				}
			}
		}
		system("cls");
		game::drawFrame(MAP_HEIGHT, MAP_WIDTH, map);
	}
}

void game::jump(int heroXCoordinate, int heroYCoordinate, game::Map** map)
{
	if((map[heroXCoordinate][heroYCoordinate + 1].passable == true) && 
		(map[heroXCoordinate][heroYCoordinate + 2].passable == true))
	{
		map[heroXCoordinate][heroYCoordinate].type = EMPTY_SPACE;
		map[heroXCoordinate][heroYCoordinate + 1].type = HERO;
		map[heroXCoordinate][heroYCoordinate + 1].healthPoints = 
			map[heroXCoordinate][heroYCoordinate].healthPoints;
		drawFrame(MAP_HEIGHT, MAP_WIDTH, map);
		map[heroXCoordinate][heroYCoordinate + 1].type = EMPTY_SPACE;
		map[heroXCoordinate][heroYCoordinate + 2].type = HERO;
		map[heroXCoordinate][heroYCoordinate + 2].healthPoints = 
			map[heroXCoordinate][heroYCoordinate + 1].healthPoints;
	}

	else if ((map[heroXCoordinate][heroYCoordinate + 1].passable == true) &&
		(map[heroXCoordinate][heroYCoordinate + 2].passable == false))
	{
		map[heroXCoordinate][heroYCoordinate].type = EMPTY_SPACE;
		map[heroXCoordinate][heroYCoordinate + 1].type = HERO;
		map[heroXCoordinate][heroYCoordinate + 1].healthPoints =
			map[heroXCoordinate][heroYCoordinate].healthPoints;
	}
}
