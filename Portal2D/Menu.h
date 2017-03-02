#pragma once

#include <iostream>
#include <conio.h>

using namespace std;

enum PlayerChoice
{
	StartGame = 49,
	Instruction = 50,
	HighScores = 51,
	Exit = 52
};

namespace menu
{
	int menu();
	void functionCaller(int playerChoice);
}
