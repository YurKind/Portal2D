#pragma once

#include <iostream>

#include <windows.h>
#include <conio.h>
#include <stdio.h> 

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

void MoveToMenuPoint3();
void MoveToMenuPoint2();
void MoveToMenuPoint();
void UserSelection3(int Cur);
void UserSelection2(int Cur);
void UserSelection(int Cur);
void RewriterCaseUpPoint3(int a);
void RewriterCaseUpPoint2(int a);
void RewriterCaseUpPoint(int a);
void RewriterCaseDownPoint3(int a);
void RewriterCaseDownPoint2(int a);
void RewriterCaseDownPoint(int a);
void Point3();
void Point2();
void Point();
void Hat();
void Stand(int x, int y, int k, char*str);

//namespace menu
//{
//	int menu();
//	void functionCaller(int playerChoice);
//}