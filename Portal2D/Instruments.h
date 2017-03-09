#pragma once

#include <iostream>

#include <Windows.h>
#include <conio.h>

#include "Definitions.h"
#include "Map.h"

namespace game
{
	struct MapCell;

	void drawFrame(MapCell** map);			// отрисовка карты, функция принимает в качетсве аргумета двумерный массив структур
	void clearScreen();					// функция очистки консоли (без мерцания) !(надо разобраться)!
}