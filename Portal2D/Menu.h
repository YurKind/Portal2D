#pragma once

#include <iostream>

#include <windows.h>
#include <conio.h>
#include <stdio.h> 

using namespace std;

enum Colors
{
	GREEN_COLOR = 10, GREEN_COLOR_DARK = 2 /*CASE_UP = 72, CASE_DOWN = 80, CASE_ENTER = 13*/
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