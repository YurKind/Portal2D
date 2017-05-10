#pragma once

#include <iostream>

#include <windows.h>
#include <conio.h>
#include <stdio.h> 

#include "Instruments.h"
#include "Records.h"
#include "Gameplay.h"
#include "Definitions.h"
#include "Queue.h"
#include "List.h"
#include "Tree.h"
#include "Structures.h"

using namespace std;

/*Параметры меню от которых зависит его вывод*/
struct ParametersForMenu
{
	int upBorder;																// Номер верхней границы меню	
	int lowerBorder;															// Номер нижней границы меню
};

namespace menu
{
	char* getFileNameFormNumberOfLevel(int numberOfLevel);

	// Рисует логотип
	void drawLogo();

	// Воспроизводит выбранный пользователем пункт в разделе Start
	void doPointStart(queue::Queue<int> *queue, bool flag);

	// Воспроизводит выбранный пользователем пункт в разделе Records
	void doPointRecords();

	void doPointRecordSearch();

	// Реализует управление меню и его вывод на экран
	int controlMenu(ParametersForMenu borders, string points[]);

	// Заполняет строковый массив
	void fillArray(string array[], int count, char divider);

	// Воспроизводит выбранный пользователем пункт в главном меню
	void doMenu(queue::Queue<int> *queue, bool flag);

	void menu();

	// Выводит меню на экран
	void printMenu(string str[], int points, int key);
}

enum Colors
{
	Black = 0,
	DarkBlue = 1,
	DarkGreen = 2,
	DarkCyan = 3,
	DarkRed = 4,
	DarkMagenta = 5,
	Brown = 6,
	LightGrey = 7,
	DarkGrey = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

enum MenuPoints
{
	Start,
	Records,
	Exit,
};

enum PointStart
{
	Instruction,
	RandomLevel,
	Level1,
	Level2,
	Level3,
	Level4,
	Level5,
	BackLevel,
};

enum PointRecords
{
	Search,
	ShowAllRecords,
	BestOfTheBest,
	BackRecords
};

enum PointRecordsSearch
{
	ByScore,
	ByLevel,
	ByName,
	BySubstring,
	BackRecordsSearch
};


