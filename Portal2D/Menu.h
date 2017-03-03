#pragma once
#include <iostream>
#include <conio.h>

using namespace std;

enum PlayerChoice
{
	START_GAME = 49,
	INSTRUCTION = 50,
	RECORDS = 51,
	EXIT = 52
};

namespace menu
{
	int menu();
	void functionCaller(int playerChoice);
}
