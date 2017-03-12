#pragma once

#include <iostream>

#include <windows.h>
#include <conio.h>
#include <stdio.h> 

#include "Records.h"
#include "Gameplay.h"
#include "Definitions.h"
#include "Queue.h"
#include "List.h"
#include "Tree.h"
#include "Structures.h"

using namespace std;

enum Colors
{
	Black = 0,
	DarkBlue = 1, 
	DarkGreen = 2,
	DarkCyan = 3, //сине-зеленый (цвет "морской волны") темный оттенок
	DarkRed = 4,
	DarkMagenta = 5, // розовый (темный оттенок)
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


enum PlayerChoice
{
	StartGame = 49,
	Instruction = 50,
	HighScores = 51,
	Exit = 52
};

void moveToMenuPoint3();
void moveToMenuPoint2();
void moveToMenuPoint();
void userSelection3(int Cur);
void userSelection2(int Cur);
void userSelection(int Cur);
void rewriterCaseUpPoint3(int a);
void rewriterCaseUpPoint2(int a);
void rewriterCaseUpPoint(int a);
void rewriterCaseDownPoint3(int a);
void rewriterCaseDownPoint2(int a);
void rewriterCaseDownPoint(int a);
void pointToMenu3();
void pointToMenu2();
void pointToMenu();
void hat();
void stand(int X_COORD, int Y_COORD, int TEXT_COLOR, char*str);
void printRecords(int Y_COORD, int TEXT_COLOR, char*str);

//namespace menu
//{
//	int menu();
//	void functionCaller(int playerChoice);
//}