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

	void drawFrame(MapCell** map);			// отрисовка карты, функция принимает в качетсве аргумета двумерный массив структур
	void clearScreen();					// функция очистки консоли (без мерцания) !(надо разобраться)!
}