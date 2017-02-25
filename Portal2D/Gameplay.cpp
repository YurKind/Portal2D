#include "Gameplay.h"

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
			default:
				break;
			}
		}
	}
	fin.close();

	return map;
}

void game::drawFrame(game::Map** map)
{
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
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

void game::moving(game::Map** map)
{
	while (true)
	{
		if (_kbhit())
		{
			int heroXCoordinate = findHeroXCoordinate(map);
			int heroYCoordinate = findHeroYCoordinate(map);
			switch (_getch())
			{
			case A_LOWER_CASE:
				if (map[heroYCoordinate][heroXCoordinate - 1].passable == true)
				{
					moveLeft(HERO, heroYCoordinate, heroXCoordinate, map);
					break;
				}
			case D_LOWER_CASE:
				if (map[heroYCoordinate][heroXCoordinate + 1].passable == true)
				{
					moveRight(HERO, heroYCoordinate, heroXCoordinate, map);
					break;
				}
			}
		}
		system("cls");
		game::drawFrame(map);
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
		drawFrame(map);
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

int game::findHeroYCoordinate(game::Map** map)
{
	for(int i = 0; i < MAP_HEIGHT; i++)
	{
		for(int j = 0; j < MAP_WIDTH; j++)
		{
			if (map[i][j].type == HERO) return i;
		}
	}
}

int game::findHeroXCoordinate(game::Map** map)
{
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (map[i][j].type == HERO) return j;
		}
	}
}

void game::moveLeft(char type, int yCoordinate, int xCoordinate, game::Map** map)
{
	map[yCoordinate][xCoordinate].type = EMPTY_SPACE;
	map[yCoordinate][xCoordinate - 1].type = type;
}

void game::moveRight(char type, int yCoordinate, int xCoordinate, game::Map** map)
{
	map[yCoordinate][xCoordinate].type = EMPTY_SPACE;
	map[yCoordinate][xCoordinate + 1].type = type;
}