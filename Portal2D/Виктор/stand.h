#pragma once
#include <iostream>
#include <windows.h>
#include <conio.h>



using namespace std;
HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
void Stand(int x, int y, int k, char*str){
	CONSOLE_CURSOR_INFO ci; ci.bVisible = 0; ci.dwSize = 100; SetConsoleCursorInfo(H, &ci); // убрать мигающий курсор
	setlocale(LC_ALL, "RUS");
	COORD c;
	c.X = x; c.Y = y;
	SetConsoleCursorPosition(H, c);
	SetConsoleTextAttribute(H, k);
	cout << str << "\n";
}