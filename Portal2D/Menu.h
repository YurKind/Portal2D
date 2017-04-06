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

/*ѕараметры меню от которых зависит его вывод*/
struct ParametersForMenu
{
	int upBorder;																// Ќомер верхней границы меню	
	int lowerBorder;															// Ќомер нижней границы меню
	void(*print)(int);															// ¬ыводит меню на экран
};

namespace menu
{
	//–исует логотип
	void drawLogo();

	//¬ыводит вариант главного меню, на котором остановилс€ пользователь
	void printMenu(int key);

	//¬ыводит вариант меню, на котором остановилс€ пользователь в пункте Start
	void printPointStart(int key);

	//¬ыводит вариант меню, на котором остановилс€ пользователь в пункте Records
	void printPointRecord(int key);

	void printPointSearch(int key);

	//¬оспроизводит выбранный пользователем пункт в разделе Start
	void doPointStart(queue::Queue<int> *queue, bool flag);

	//¬оспроизводит выбранный пользователем пункт в разделе Records
	void doPointRecords();

	void doPointRecordSearch();

	//–еализует управление меню и его вывод на экран
	int controlMenu(ParametersForMenu borders);

	//¬оспроизводит выбранный пользователем пункт в главном меню
	void menu(queue::Queue<int> *queue, bool flag);
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
	Start = 1,
	Records,
	Exit,
};

enum PointStart
{
	Instruction = 1,
	RandomLevel,
	Level1,
	Level2,
	BackLevel,
};

enum PointRecords
{
	Search = 1,
	ShowAllRecords,
	Show10Records,
	BestOfTheBest,
	BackRecords
};

enum PointRecordsSearch
{
	ByScore = 1,
	ByLevel,
	ByName,
	BySubstring,
	BackRecordsSearch
};


