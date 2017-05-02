#include "Gameplay.h"
#include "Map.h"
#include "Definitions.h"
#include "Instruments.h"
#include "List.h"

// функция считывающая карту из файла в двумерный массив структур, функция принимает в качетсве аргумета имя уровня
game::MapCell** game::createMap(char* levelName, GameInfo* gameInfo)
{
	game::MapCell** map = new game::MapCell*[MAP_HEIGHT];	//создание динамического массива
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		map[i] = new game::MapCell[MAP_WIDTH];
	}

	char currentSymbol;	// переменная для временного хранения текущего символа, считанного из файла
	std::ifstream fin(levelName, std::ios_base::in);

	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			currentSymbol = fin.get();
			if (currentSymbol == NEW_LINE)	// если символ равен '\n', то происходит считывание следующего символа
				currentSymbol = fin.get();

			switch (currentSymbol)			 
			{
			case HERO_SYMBOL:
				map[i][j].types = new list::List<char>;
				list::addBegin(&map[i][j].types, EMPTY_SPACE);
				list::addBegin(&map[i][j].types, HERO);
				gameInfo->hero.xCoordinate = j;
				gameInfo->hero.yCoordinate = i;
				break;

			case BLOCK_SHARP:
				map[i][j].types = new list::List<char>;
				list::addBegin(&map[i][j].types, BLOCK);
				map[i][j].passable = false;
				break;

			case EMPTY_SPACE:
				map[i][j].types = new list::List<char>;
				list::addBegin(&map[i][j].types, EMPTY_SPACE);
				break;

			case AIM_DOT:
				map[i][j].types = new list::List<char>;
				list::addBegin(&map[i][j].types, EMPTY_SPACE);
				list::addBegin(&map[i][j].types, AIM_DOT);
				gameInfo->aim.xCoordinate = j;
				gameInfo->aim.yCoordinate = i;
				break;

			case BLACK_WALL_ONE_S:
				map[i][j].types = new list::List<char>;
				list::addBegin(&map[i][j].types, EMPTY_SPACE);
				list::addBegin(&map[i][j].types, BLACK_WALL);
				gameInfo->blackWallOne.xCoordinate = j;
				gameInfo->blackWallOne.yCoordinate = i;
				map[i][j].passable = false;
				break;

			case BLACK_WALL_TWO_S:
				map[i][j].types = new list::List<char>;
				list::addBegin(&map[i][j].types, EMPTY_SPACE);
				list::addBegin(&map[i][j].types, BLACK_WALL);
				gameInfo->blackWallTwo.xCoordinate = j;
				gameInfo->blackWallTwo.yCoordinate = i;
				map[i][j].passable = false;
				break;

			case BLACK_WALL_THREE_S:
				map[i][j].types = new list::List<char>;
				list::addBegin(&map[i][j].types, EMPTY_SPACE);
				list::addBegin(&map[i][j].types, BLACK_WALL);
				gameInfo->blackWallThree.xCoordinate = j;
				gameInfo->blackWallThree.yCoordinate = i;
				map[i][j].passable = false;
				break;

			case BLACK_WALL_FOUR_S:
				map[i][j].types = new list::List<char>;
				list::addBegin(&map[i][j].types, EMPTY_SPACE);
				list::addBegin(&map[i][j].types, BLACK_WALL);
				gameInfo->blackWallFour.xCoordinate = j;
				gameInfo->blackWallFour.yCoordinate = i;
				map[i][j].passable = false;
				break;

			case EXIT_S:
				map[i][j].types = new list::List<char>;
				list::addBegin(&map[i][j].types, EMPTY_SPACE);
				list::addBegin(&map[i][j].types, EXIT);
				gameInfo->exitFromLevel.xCoordinate = j;
				gameInfo->exitFromLevel.yCoordinate = i;
				break;

			case BUTTON_ONE_S:
				map[i][j].types = new list::List<char>;
				list::addBegin(&map[i][j].types, EMPTY_SPACE);
				list::addBegin(&map[i][j].types, BUTTON);
				gameInfo->buttonOne.xCoordinate = j;
				gameInfo->buttonOne.yCoordinate = i;
				break;
				
			case BUTTON_TWO_S:
				map[i][j].types = new list::List<char>;
				list::addBegin(&map[i][j].types, EMPTY_SPACE);
				list::addBegin(&map[i][j].types, BUTTON);
				gameInfo->buttonTwo.xCoordinate = j;
				gameInfo->buttonTwo.yCoordinate = i;
				break;

			case BUTTON_THREE_S:
				map[i][j].types = new list::List<char>;
				list::addBegin(&map[i][j].types, EMPTY_SPACE);
				list::addBegin(&map[i][j].types, BUTTON);
				gameInfo->buttonThree.xCoordinate = j;
				gameInfo->buttonThree.yCoordinate = i;
				break;

			case BUTTON_FOUR_S:
				map[i][j].types = new list::List<char>;
				list::addBegin(&map[i][j].types, EMPTY_SPACE);
				list::addBegin(&map[i][j].types, BUTTON);
				gameInfo->buttonFour.xCoordinate = j;
				gameInfo->buttonFour.yCoordinate = i;
				break;

			case TURRET_HUNTER_S:
				map[i][j].types = new list::List<char>;
				list::addBegin(&map[i][j].types, EMPTY_SPACE);
				list::addBegin(&map[i][j].types, TURRET_HUNTER);
				gameInfo->hunter_turret.xCoordinate = j;
				gameInfo->hunter_turret.yCoordinate = i;
				break;

			case STATIONARY_TURRET_S:
				map[i][j].types = new list::List<char>;
				list::addBegin(&map[i][j].types, EMPTY_SPACE);
				list::addBegin(&map[i][j].types, STATIONARY_TURRET);
				gameInfo->stationary_turret.xCoordinate = j;
				gameInfo->stationary_turret.yCoordinate = i;
				break;

			case PLATFORM_TURRET_S:
				map[i][j].types = new list::List<char>;
				list::addBegin(&map[i][j].types, EMPTY_SPACE);
				list::addBegin(&map[i][j].types, PLATFORM_TURRET);
				gameInfo->platform_turret.xCoordinate = j;
				gameInfo->platform_turret.yCoordinate = i;
				break;

			case WALL:
				map[i][j].types = new list::List<char>;
				list::addBegin(&map[i][j].types, EMPTY_SPACE);
				list::addBegin(&map[i][j].types, WALL);
				gameInfo->wall.xCoordinate = j;
				gameInfo->wall.yCoordinate = i;
				break;

			case BLUE_PORTAL:
				map[i][j].types = new list::List<char>;
				list::addBegin(&map[i][j].types, EMPTY_SPACE);
				list::addBegin(&map[i][j].types, BLUE_PORTAL);
				gameInfo->bluePortal.xCoordinate = j;
				gameInfo->bluePortal.yCoordinate = i;
				break;

			case RED_PORTAL:
				map[i][j].types = new list::List<char>;
				list::addBegin(&map[i][j].types, EMPTY_SPACE);
				list::addBegin(&map[i][j].types, RED_PORTAL);
				gameInfo->redPortal.xCoordinate = j;
				gameInfo->redPortal.yCoordinate = i;
				break;

			default:
				break;
			}
		}
	}

	fin.close();

	return map;
}
