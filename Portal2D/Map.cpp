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

			case BLACK_WALL_S:
				map[i][j].types = new list::List<char>;
				list::addBegin(&map[i][j].types, EMPTY_SPACE);
				list::addBegin(&map[i][j].types, BLACK_WALL);
				gameInfo->blackWall.xCoordinate = j;
				gameInfo->blackWall.yCoordinate = i;
				map[i][j].passable = false;
				break;

			case EXIT_S:
				map[i][j].types = new list::List<char>;
				list::addBegin(&map[i][j].types, EMPTY_SPACE);
				list::addBegin(&map[i][j].types, EXIT);
				gameInfo->exitFromLevel.xCoordinate = j;
				gameInfo->exitFromLevel.yCoordinate = i;
				break;

			case BUTTON_S:
				map[i][j].types = new list::List<char>;
				list::addBegin(&map[i][j].types, BUTTON);
				gameInfo->button.xCoordinate = j;
				gameInfo->button.yCoordinate = i;
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

			default:
				break;
			}
		}
	}

	fin.close();

	return map;
}
