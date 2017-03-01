#pragma once

#include <iostream>

#include <Windows.h>
#include <conio.h>

#include "Definitions.h"
#include "Map.h"

namespace game
{
	int findHeroXCoordinate(MapShell** map);	// функция ищет координаты пресонажа по X и возвращает их, функция принимает в качетсве аргумета двумерный массив структур
	int findHeroYCoordinate(MapShell** map);	// функция ищет координаты пресонажа по Y и возвращает их, функция принимает в качетсве аргумета двумерный массив структур

	int findAimXCoordinate(MapShell** map);  // функция ищет координаты прицела по X и возвращает их, функция принимает в качетсве аргумета двумерный массив структур
	int findAimYCoordinate(MapShell** map);	// функция ищет координаты прицела по Y и возвращает их, функция принимает в качетсве аргумета двумерный массив структур

	int findPortalXCoordinate(char type, MapShell** map);
	int findPortalYCoordinate(char type, MapShell** map);

	void drawFrame(MapShell** map);			// отрисовка карты, функция принимает в качетсве аргумета двумерный массив структур
	void clearScreen();					// функция очистки консоли (без мерцания) !(надо разобраться)!
}