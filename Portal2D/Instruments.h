#pragma once

#include <iostream>

#include <Windows.h>
#include <conio.h>

#include "DistrOfDefine.h"
#include "Map.h"

namespace game
{
	int findHeroXCoordinate(Map** map);	// функция ищет координаты пресонажа по X и возвращает их
	int findHeroYCoordinate(Map** map);	// функция ищет координаты пресонажа по Y и возвращает их

	int findAimXCoordinate(Map** map);  // функция ищет координаты прицела по X и возвращает их
	int findAimYCoordinate(Map** map);	// функция ищет координаты прицела по Y и возвращает их

	void drawFrame(Map** map);			// отрисовка карты
	void clearScreen();					// функция очистки консоли (без мерцания) !(надо разобраться)!
}