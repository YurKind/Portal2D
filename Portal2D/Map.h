#pragma once

#include "Definitions.h"
#include "Instruments.h"

namespace game
{
	struct MapShell					// структура MapShell хранит всебе данные об элементе массива структур
	{
		char type;					// переменная для хранения текстуры (персонажа, блоков и тд)
		int xCoordinate;			// координаты по x ?(оно пригодится в будущем)?
		int yCoordinate;			// координаты по y ???
		bool passable;				// переменная хранит в себе данные о возможности пройти сквозь неё
		int healthPoints = 100;		// здоровье персонажей
	};

	// функция считывающая карту из файла в двумерный массив структур, функция принимает в качетсве аргумета имя уровня
	MapShell** createMap(char* levelName);
}
