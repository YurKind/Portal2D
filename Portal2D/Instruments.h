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

	void drawFrame(MapShell** map);			// отрисовка карты, функция принимает в качетсве аргумета двумерный массив структур
	void clearScreen();					// функция очистки консоли (без мерцания) !(надо разобраться)!
}