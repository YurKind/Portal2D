#pragma once

#include <iostream>

#include <Windows.h>
#include <conio.h>

#include "Definitions.h"

namespace game
{
	struct MapShell;

	struct StackOfTypes
	{
		char type;
		StackOfTypes* next;
	};

	//void push(char type, MapShell* &next);
	//char pop(MapShell* &next);

	int findSomeTypeXCoordinate(char type, MapShell** map);	// функция ищет координаты "объекта_на_карте" по X и возвращает их, функция принимает в качетсве аргумета двумерный массив структур
	int findSomeTypeYCoordinate(char type, MapShell** map);	// функция ищет координаты "объекта_на_карте" по Y и возвращает их, функция принимает в качетсве аргумета двумерный массив структур

	void drawFrame(MapShell** map);			// отрисовка карты, функция принимает в качетсве аргумета двумерный массив структур
	void clearScreen();					// функция очистки консоли (без мерцания) !(надо разобраться)!
}