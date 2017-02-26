#include "DistrOfDefine.h"
#include "Map.h"
#include "Instruments.h"

int game::findHeroYCoordinate(game::Map** map)		// функция ищет координаты пресонажа по Y и возвращает их
{
	for (int i = 0; i < MAP_HEIGHT; i++)			// цикл ищет с символ обозначающий героя
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (map[i][j].type == HERO) return i;	// когда встречен искомый сивол, функция возвращает Y координату
		}
	}
}

int game::findHeroXCoordinate(game::Map** map)		// функция ищет координаты пресонажа по X и возвращает их
{
	for (int i = 0; i < MAP_HEIGHT; i++)			// цикл ищет с символ обозначающий героя
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (map[i][j].type == HERO) return j;	// когда встречен искомый сивол, функция возвращает X координату
		}
	}
}

int game::findAimXCoordinate(game::Map** map)		// функция ищет координаты прицела по X и возвращает их
{
	{
		for (int i = 0; i < MAP_HEIGHT; i++)
		{
			for (int j = 0; j < MAP_WIDTH; j++)
			{
				if (map[i][j].type == AIM_DOT) return j;	// когда встречен искомый сивол, функция возвращает X координату
			}
		}
	}
}

int game::findAimYCoordinate(game::Map** map)		// функция ищет координаты прицела по Y и возвращает их
{
	{
		for (int i = 0; i < MAP_HEIGHT; i++)
		{
			for (int j = 0; j < MAP_WIDTH; j++)
			{
				if (map[i][j].type == AIM_DOT) return i;	// когда встречен искомый сивол, функция возвращает Y координату
			}
		}
	}
}


void game::drawFrame(game::Map** map)		// отрисовка карты
{
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			switch (map[i][j].type)			// выражением служит тип текущего элемента массива (персонаж, блок и тд)
			{
			case HERO:						// если встречен тип "герой", то отрисовывается герой
				std::cout << HERO;
				break;

			case BLOCK:						// если встречен тип "блок", то отрисовывается блок
				std::cout << BLOCK;
				break;

			case EMPTY_SPACE:				// если встречен тип "_", то отрисовывается пустое пространство
				std::cout << EMPTY_SPACE;
				break;

			case AIM_DOT:					// если встречен тип "прицел_точка", то отрисовывается прицел
				std::cout << AIM;
				break;
				
			case BLACK_WALL:				// если встречен тип "непроходимая стена", то отрисовывается непроходимая стена
				std::cout << BLACK_WALL;
				break;

			case EXIT:					// если встречен тип "выход", то отрисовывается выход
				std::cout << EXIT;
				break;

			default:
				break;
			}
		}
		std::cout << std::endl;
	}
}

void game::clearScreen()		// функция очистки консоли (без мерцания)
{
	HANDLE Handle = nullptr;
	Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Cursor;
	Cursor.X = 0;
	Cursor.Y = 0;
	SetConsoleCursorPosition(Handle, Cursor);
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(Handle, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(Handle, &structCursorInfo);
}
