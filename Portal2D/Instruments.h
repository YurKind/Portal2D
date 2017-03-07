#pragma once

#include <iostream>

#include <Windows.h>
#include <conio.h>

#include "Definitions.h"

namespace game
{
	struct MapCell;

	struct StackOfTypes
	{
		char type;
		StackOfTypes* next;
	};

	//void push(char type, MapCell* &next);
	//char pop(MapCell* &next);

<<<<<<< HEAD
	//int findSomeTypeXCoordinate(char type, MapShell** map);	// функция ищет координаты "объекта_на_карте" по X и возвращает их, функция принимает в качетсве аргумета двумерный массив структур
	//int findSomeTypeYCoordinate(char type, MapShell** map);	// функция ищет координаты "объекта_на_карте" по Y и возвращает их, функция принимает в качетсве аргумета двумерный массив структур

	void drawFrame(MapShell** map);			// отрисовка карты, функция принимает в качетсве аргумета двумерный массив структур
=======
	void drawFrame(MapCell** map);			// отрисовка карты, функция принимает в качетсве аргумета двумерный массив структур
>>>>>>> Andrey
	void clearScreen();					// функция очистки консоли (без мерцания) !(надо разобраться)!
}