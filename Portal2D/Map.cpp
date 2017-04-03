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
			case HERO_SYMBOL:					// если текущий символ равен "H", то
				map[i][j].types = new list::List<char>;
				list::addBegin(&map[i][j].types, EMPTY_SPACE);
				list::addBegin(&map[i][j].types, HERO);
				gameInfo->hero.xCoordinate = j;	// запоминаются его координаты
				gameInfo->hero.yCoordinate = i;
				map[i][j].passable = true;
				break;

			case BLOCK_SHARP:				// если текущий символ равен "решётка", то
				map[i][j].types = new list::List<char>;
				list::addBegin(&map[i][j].types, BLOCK);
				map[i][j].passable = false;	//клетка становится непроходимой
				break;

			case EMPTY_SPACE:				// если текущий символ равен "_", то
				map[i][j].types = new list::List<char>;
				list::addBegin(&map[i][j].types, EMPTY_SPACE);
				map[i][j].passable = true;	// клетка становится проходимой
				break;

			case AIM_DOT:					// если текущий символ равен "точке", то
				map[i][j].types = new list::List<char>;
				list::addBegin(&map[i][j].types, EMPTY_SPACE);
				list::addBegin(&map[i][j].types, AIM_DOT);
				gameInfo->aim.xCoordinate = j;	// запоминаются его координаты
				gameInfo->aim.yCoordinate = i;
				map[i][j].passable = true;	// клетка становится проходимой
				break;

			case BLACK_WALL_S:				// если текущий символ равен "X", то
				map[i][j].types = new list::List<char>;
				list::addBegin(&map[i][j].types, EMPTY_SPACE);
				list::addBegin(&map[i][j].types, BLACK_WALL);
				gameInfo->blackWall.xCoordinate = j;
				gameInfo->blackWall.yCoordinate = i;
				map[i][j].passable = false;	// клетка становится непроходимой
				break;

			case EXIT_S:					// если текущий символ равен "X", то
				map[i][j].types = new list::List<char>;
				list::addBegin(&map[i][j].types, EMPTY_SPACE);
				list::addBegin(&map[i][j].types, EXIT);
				gameInfo->exitFromLevel.xCoordinate = j;
				gameInfo->exitFromLevel.yCoordinate = i;
				map[i][j].passable = true;	// клетка становится проходимой
				break;

			case BUTTON_S:
				map[i][j].types = new list::List<char>;
				list::addBegin(&map[i][j].types, BUTTON);
				gameInfo->button.xCoordinate = j;
				gameInfo->button.yCoordinate = i;
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
