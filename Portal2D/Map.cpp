#include "Gameplay.h"
#include "Map.h"

<<<<<<< HEAD
// функция считывающая карту из файла в двумерный массив структур, функция принимает в качетсве аргумета имя уровня
game::MapShell** game::createMap(char* levelName, Hero* hero, Aim* aim, RedPortal* redPortal, BluePotal* bluePortal)
=======
// функция считывающая карту из файла в двумерный массив структур, принимает в качестве аргумента имя уровня
game::Map** game::createMap(char* levelName)
>>>>>>> Andrey
{
	game::MapShell** map = new game::MapShell*[MAP_HEIGHT];	//создание динамического массива
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		map[i] = new game::MapShell[MAP_WIDTH];
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

			switch (currentSymbol)			// 
			{
			case HERO_SYMBOL:				// если текущий символ равен "H", то
				map[i][j].type = HERO;		// тип текущей клетки становится "Герой"
				hero->xCoordinate = j;	// запоминаются его координаты
				hero->yCoordinate = i;
				map[i][j].passable = true;
				break;

			case BLOCK_SHARP:				// если текущий символ равен "решётка", то
				map[i][j].type = BLOCK;		// тип текущей клетки становится "Блок"
				map[i][j].xCoordinate = j;	// запоминаются его координаты
				map[i][j].yCoordinate = i;
				map[i][j].passable = false;	//клетка становится непроходимой
				break;

			case EMPTY_SPACE:				// если текущий символ равен "_", то
				map[i][j].type = EMPTY_SPACE;	// тип текущей клетки становится "пустое пространство"
				map[i][j].xCoordinate = j;		// запоминаются её координаты
				map[i][j].yCoordinate = i;
				map[i][j].passable = true;	// клетка становится проходимой
				break;

			case AIM_DOT:					// если текущий символ равен "точке", то
				map[i][j].type = AIM_DOT;	// тип текущей клетки становится "прицел"
				aim->xCoordinate = j;	// запоминаются его координаты
				aim->yCoordinate = i;
				map[i][j].passable = true;	// клетка становится проходимой
				break;

			case BLACK_WALL_S:				// если текущий символ равен "X", то
				map[i][j].type = BLACK_WALL;	// тип текущей клетки становится "непроходимая стена"
				map[i][j].xCoordinate = j;	// запоминаются его координаты
				map[i][j].yCoordinate = i;
				map[i][j].passable = false;	// клетка становится непроходимой
				break;

			case EXIT_S:					// если текущий символ равен "X", то
				map[i][j].type = EXIT;		// тип текущей клетки становится "выход"
				map[i][j].xCoordinate = j;	// запоминаются его координаты
				map[i][j].yCoordinate = i;
				map[i][j].passable = true;	// клетка становится проходимой
				break;

			case RED_PORTAL:
				map[i][j].type = RED_PORTAL;
				map[i][j].xCoordinate = j;
				map[i][j].yCoordinate = i;
				map[i][j].passable = true;
				break;

			case BLUE_PORTAL:
				map[i][j].type = BLUE_PORTAL;
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
