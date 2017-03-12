#include "Gameplay.h"
#include "Map.h"

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
				map[i][j].types = new Stack<char>;
				push(EMPTY_SPACE, map[i][j].types);			// тип текущей клетки становится "Герой"
				push(HERO, map[i][j].types);
				gameInfo->hero.xCoordinate = j;	// запоминаются его координаты
				gameInfo->hero.yCoordinate = i;
				map[i][j].passable = true;
				break;

			case BLOCK_SHARP:				// если текущий символ равен "решётка", то
				map[i][j].types = new Stack<char>;
				push(BLOCK, map[i][j].types);		// тип текущей клетки становится "Блок"
				map[i][j].passable = false;	//клетка становится непроходимой
				break;

			case EMPTY_SPACE:				// если текущий символ равен "_", то
				map[i][j].types = new Stack<char>;
				push(EMPTY_SPACE, map[i][j].types);	// тип текущей клетки становится "пустое пространство"
				map[i][j].passable = true;	// клетка становится проходимой
				break;

			case AIM_DOT:					// если текущий символ равен "точке", то
				map[i][j].types = new Stack<char>;
				push(EMPTY_SPACE, map[i][j].types);
				push(AIM_DOT, map[i][j].types);	// тип текущей клетки становится "прицел"
				gameInfo->aim.xCoordinate = j;	// запоминаются его координаты
				gameInfo->aim.yCoordinate = i;
				map[i][j].passable = true;	// клетка становится проходимой
				break;

			case BLACK_WALL_S:				// если текущий символ равен "X", то
				map[i][j].types = new Stack<char>;
				push(EMPTY_SPACE, map[i][j].types);
				push(BLACK_WALL, map[i][j].types);	// тип текущей клетки становится "непроходимая стена"
				gameInfo->blackWall.xCoordinate = j;
				gameInfo->blackWall.yCoordinate = i;
				map[i][j].passable = false;	// клетка становится непроходимой
				break;

			case EXIT_S:					// если текущий символ равен "X", то
				map[i][j].types = new Stack<char>;
				push(EMPTY_SPACE, map[i][j].types);
				push(EXIT, map[i][j].types);		// тип текущей клетки становится "выход"
				gameInfo->exitFromLevel.xCoordinate = j;
				gameInfo->exitFromLevel.yCoordinate = i;
				map[i][j].passable = true;	// клетка становится проходимой
				break;

			case RED_PORTAL:				  // если текущий символ равен "O", то
				map[i][j].types = new Stack<char>;
				push(RED_PORTAL, map[i][j].types);  // тип текущей клетки становится "красный портал"
				gameInfo->redPortal.xCoordinate = j;
				gameInfo->redPortal.yCoordinate = i;   // запоминаются его координаты
				map[i][j].passable = true;    // клетка становится проходимой
				break;

			case BLUE_PORTAL:
				map[i][j].types = new Stack<char>;
				push(BLUE_PORTAL, map[i][j].types);   // если текущий символ равен "O", то
				gameInfo->bluePortal.xCoordinate = j;    // тип текущей клетки становится "красный портал"
				gameInfo->bluePortal.yCoordinate = i;	// запоминаются его координаты
				map[i][j].passable = true;      // клетка становится проходимой
				break;

			case BUTTON_S:
				map[i][j].types = new Stack<char>;
				push(BUTTON, map[i][j].types);
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
