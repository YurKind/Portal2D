#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>

#include <Windows.h>
#include <conio.h>

#include "Definitions.h"
#include "Map.h"

// За модуль отвечают: Меньшиков Юрий и Наговицин Максим
namespace game
{
	// отрисовка карты, функция принимает в качетсве аргумета двумерный массив структур
	void drawFrame(MapCell** map, GameInfo* gameInfo);

	// функция очистки консоли (без мерцания)
	void clearScreen();
	
	// отчиствка памяти
	void freeMemory(MapCell** map, GameInfo* gameInfo);
	
	// вывод определённого символа в заданное место карты
	void printSpecialSymbol(HANDLE consoleHandler, int yCoordinate, int xCoordinate, int color, char symbol);
	
	// вычисление очков, набранных игроком
	double computeTheScore(GameInfo* gameInfo);
	
	// вывод инструкций к игре
	void showInstruction();
}

