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
				map[i][j].types = NULL;
				list::addBegin(&map[i][j].types, EMPTY_SPACE);
				list::addBegin(&map[i][j].types, HERO);
				gameInfo->hero.coordinates.xCoordinate = j;
				gameInfo->hero.coordinates.yCoordinate = i;
				break;

			case BLOCK_SHARP:
				map[i][j].types = NULL;
				list::addBegin(&map[i][j].types, BLOCK);
				map[i][j].passable = false;
				break;

			case EMPTY_SPACE:
				map[i][j].types = NULL;
				list::addBegin(&map[i][j].types, EMPTY_SPACE);
				break;

			case AIM_DOT:
				map[i][j].types = NULL;
				list::addBegin(&map[i][j].types, EMPTY_SPACE);
				list::addBegin(&map[i][j].types, AIM_DOT);
				gameInfo->aim.coordinates.xCoordinate = j;
				gameInfo->aim.coordinates.yCoordinate = i;
				break;

			case BLACK_WALL_ONE_S:
				map[i][j].types = NULL;
				list::addBegin(&map[i][j].types, EMPTY_SPACE);
				list::addBegin(&map[i][j].types, BLACK_WALL);
				gameInfo->blackWallOne.coordinates.xCoordinate = j;
				gameInfo->blackWallOne.coordinates.yCoordinate = i;
				map[i][j].passable = false;
				break;

			case BLACK_WALL_TWO_S:
				map[i][j].types = NULL;
				list::addBegin(&map[i][j].types, EMPTY_SPACE);
				list::addBegin(&map[i][j].types, BLACK_WALL);
				gameInfo->blackWallTwo.coordinates.xCoordinate = j;
				gameInfo->blackWallTwo.coordinates.yCoordinate = i;
				map[i][j].passable = false;
				break;

			case BLACK_WALL_THREE_S:
				map[i][j].types = NULL;
				list::addBegin(&map[i][j].types, EMPTY_SPACE);
				list::addBegin(&map[i][j].types, BLACK_WALL);
				gameInfo->blackWallThree.coordinates.xCoordinate = j;
				gameInfo->blackWallThree.coordinates.yCoordinate = i;
				map[i][j].passable = false;
				break;

			case BLACK_WALL_FOUR_S:
				map[i][j].types = NULL;
				list::addBegin(&map[i][j].types, EMPTY_SPACE);
				list::addBegin(&map[i][j].types, BLACK_WALL);
				gameInfo->blackWallFour.coordinates.xCoordinate = j;
				gameInfo->blackWallFour.coordinates.yCoordinate = i;
				map[i][j].passable = false;
				break;

			case EXIT_S:
				map[i][j].types = NULL;
				list::addBegin(&map[i][j].types, EMPTY_SPACE);
				list::addBegin(&map[i][j].types, EXIT);
				gameInfo->exitFromLevel.coordinates.xCoordinate = j;
				gameInfo->exitFromLevel.coordinates.yCoordinate = i;
				break;

			case BUTTON_ONE_S:
				map[i][j].types = NULL;
				list::addBegin(&map[i][j].types, EMPTY_SPACE);
				list::addBegin(&map[i][j].types, BUTTON);
				gameInfo->buttonOne.coordinates.xCoordinate = j;
				gameInfo->buttonOne.coordinates.yCoordinate = i;
				break;
				
			case BUTTON_TWO_S:
				map[i][j].types = NULL;
				list::addBegin(&map[i][j].types, EMPTY_SPACE);
				list::addBegin(&map[i][j].types, BUTTON);
				gameInfo->buttonTwo.coordinates.xCoordinate = j;
				gameInfo->buttonTwo.coordinates.yCoordinate = i;
				break;

			case BUTTON_THREE_S:
				map[i][j].types = NULL;
				list::addBegin(&map[i][j].types, EMPTY_SPACE);
				list::addBegin(&map[i][j].types, BUTTON);
				gameInfo->buttonThree.coordinates.xCoordinate = j;
				gameInfo->buttonThree.coordinates.yCoordinate = i;
				break;

			case BUTTON_FOUR_S:
				map[i][j].types = NULL;
				list::addBegin(&map[i][j].types, EMPTY_SPACE);
				list::addBegin(&map[i][j].types, BUTTON);
				gameInfo->buttonFour.coordinates.xCoordinate = j;
				gameInfo->buttonFour.coordinates.yCoordinate = i;
				break;

			case TURRET_HUNTER_S:
				map[i][j].types = NULL;
				list::addBegin(&map[i][j].types, EMPTY_SPACE);
				list::addBegin(&map[i][j].types, TURRET_HUNTER);
				gameInfo->hunter_turret.coordinates.xCoordinate = j;
				gameInfo->hunter_turret.coordinates.yCoordinate = i;
				break;

			case STATIONARY_TURRET_S:
				map[i][j].types = NULL;
				list::addBegin(&map[i][j].types, EMPTY_SPACE);
				list::addBegin(&map[i][j].types, STATIONARY_TURRET);
				gameInfo->stationary_turret.coordinates.xCoordinate = j;
				gameInfo->stationary_turret.coordinates.yCoordinate = i;
				break;

			case PLATFORM_TURRET_S:
				map[i][j].types = NULL;
				list::addBegin(&map[i][j].types, EMPTY_SPACE);
				list::addBegin(&map[i][j].types, PLATFORM_TURRET);
				gameInfo->platform_turret.coordinates.xCoordinate = j;
				gameInfo->platform_turret.coordinates.yCoordinate = i;
				break;

			case WALL:
				map[i][j].types = NULL;
				list::addBegin(&map[i][j].types, EMPTY_SPACE);
				list::addBegin(&map[i][j].types, WALL);
				gameInfo->wall.coordinates.xCoordinate = j;
				gameInfo->wall.coordinates.yCoordinate = i;
				break;

			case BLUE_PORTAL:
				map[i][j].types = NULL;
				list::addBegin(&map[i][j].types, EMPTY_SPACE);
				list::addBegin(&map[i][j].types, BLUE_PORTAL);
				gameInfo->bluePortal.coordinates.xCoordinate = j;
				gameInfo->bluePortal.coordinates.yCoordinate = i;
				break;

			case RED_PORTAL:
				map[i][j].types = NULL;
				list::addBegin(&map[i][j].types, EMPTY_SPACE);
				list::addBegin(&map[i][j].types, RED_PORTAL);
				gameInfo->redPortal.coordinates.xCoordinate = j;
				gameInfo->redPortal.coordinates.yCoordinate = i;
				break;

			default:
				break;
			}
		}
	}

	fin.close();

	return map;
}
