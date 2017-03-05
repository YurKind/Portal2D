#pragma once

#include <iostream>

#include <Windows.h>
#include <conio.h>

#include "Definitions.h"

namespace game
{
<<<<<<< HEAD
	struct MapShell;

	struct StackOfTypes
	{
		char type;
		StackOfTypes* next;
	};
=======
	int findHeroXCoordinate(Map** map);	// функция ищет координаты пресонажа по X и возвращает их, в качестве аргумента принимает двумерный массив структур
	int findHeroYCoordinate(Map** map);	// функция ищет координаты пресонажа по Y и возвращает их, в качестве аргумента принимает двумерный массив структур

	int findAimXCoordinate(Map** map);  // функция ищет координаты прицела по X и возвращает их, в качестве аргумента принимает двумерный массив структур
	int findAimYCoordinate(Map** map);	// функция ищет координаты прицела по Y и возвращает их, в качестве аргумента принимает двумерный массив структур
>>>>>>> Andrey

	//void push(char type, MapShell* &next);
	//char pop(MapShell* &next);

	int findSomeTypeXCoordinate(char type, MapShell** map);	// функция ищет координаты "объекта_на_карте" по X и возвращает их, функция принимает в качетсве аргумета двумерный массив структур
	int findSomeTypeYCoordinate(char type, MapShell** map);	// функция ищет координаты "объекта_на_карте" по Y и возвращает их, функция принимает в качетсве аргумета двумерный массив структур

	void drawFrame(MapShell** map);			// отрисовка карты, функция принимает в качетсве аргумета двумерный массив структур
	void clearScreen();					// функция очистки консоли (без мерцания) !(надо разобраться)!
}