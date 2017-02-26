#pragma once

#include "DistrOfDefine.h"

namespace game
{
	struct Map						// структура Map хранит всебе данные об элементе массива структур
	{
		char type;					// переменная для хранения текстуры (персонажа, блоков и тд)
		int xCoordinate;			// координаты по x ?(оно пригодится в будущем)?
		int yCoordinate;			// координаты по y ???
		bool passable;				// переменная хранит в себе данные о возможности пройти сквозь неё
		int healthPoints = 100;		// здоровье персонажей
	};

	Map** createMap(char* levelName);	// функция считывающая карту из файла в двумерный массив структур
}