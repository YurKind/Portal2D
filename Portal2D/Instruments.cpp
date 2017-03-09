#include "Definitions.h"
#include "Map.h"
#include "Instruments.h"

void game::drawFrame(game::MapCell** map)		// отрисовка карты, функция принимает в качетсве аргумета двумерный массив структур
{
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			switch (peek(map[i][j].types))			// выражением служит тип текущего элемента массива (персонаж, блок и тд)
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

			case RED_PORTAL:			// если встречен тип "красный портал", то отрисовывается красный портал
				std::cout << RED_PORTAL;
				break;

			case BLUE_PORTAL:			// если встречен тип "синий портал", то отрисовывается синий портал
				std::cout << BLUE_PORTAL;
				break;

			case BUTTON:
				std::cout << BUTTON;
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

//void game::push(char type, MapCell* &topElement)
//{
//	MapCell* newType = new MapCell;
//	newType->type = type;
//	newType->next = topElement;
//	topElement = newType;
//}
//
//char game::pop(MapCell* &topElement)
//{
//	char temp = topElement->type;
//	MapCell* currentElement = topElement;
//	topElement = topElement->next;
//	delete currentElement;
//	return temp;
//}