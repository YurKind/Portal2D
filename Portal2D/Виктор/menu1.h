#pragma once
#include <iostream>
#include <windows.h>
#include <conio.h>
#include "stand.h"
#include "menu2.h"

using namespace std;

 void menu1()
{
	const int rowsCount = 5;
	const int columnsCount = 55;
	const unsigned char levelData[rowsCount][columnsCount + 1] =
	{
		//заполнение массива-карты
		"           ***   **** ***  ***  *   *     ***  ***   ",
		"           *  *  *  * *  *  *  * *  *       *  *  *  ",
		"           ***   *  * * *   * * * * *     * *  *  *  ",
		"           *     *  * *  *  * *   * *     *    *  *  ",
		"           *     **** *  *  * *   * ***   ***  ***   ",

	};
	printf("\t");
	for (int r = 0; r <rowsCount; r++)
	{
		for (int c = 0; c < columnsCount; c++)
		{
			unsigned char symbol = levelData[r][c];
			printf("%c", symbol);
		}
		printf("\n\t");

	}

	Stand(30, 9, 10, "Start game");
	Stand(30, 11, 2, "Records");
	Stand(30, 13, 2, "Exit");


	int k; // код клавиши
	int cur = 1; // какой пункт выбран сейчас
	while (1){
		k = _getch();
		if (k == 80){
			if (cur<3){
				cur++;
				if (cur == 2){
					Stand(30, 9, 2, "Start game");
					Stand(30, 11, 10, "Records");
				}
				else if (cur == 3){
					Stand(30, 11, 2, "Records");
					Stand(30, 13, 10, "Exit");
				}

			}
		}
		else if (k == 72){
			if (cur>1){
				cur--;
				if (cur == 3){
					Stand(30, 13, 10, "Exit");

				}
				else if (cur == 2){
					Stand(30, 11, 10, "Records");
					Stand(30, 13, 2, "Exit");
				}
				else if (cur == 1){
					Stand(30, 9, 10, "Start game");
					Stand(30, 11, 2, "Records");
				}
			}
		}
		else if (k == 13){
			system("cls");
			SetConsoleTextAttribute(H, 12);
			if (cur == 1)  menu2();
			else if (cur == 2) cout << "–екорды!\n\n";

			else cout << "¬ыход!\n\n";
			_getch();
			exit(0);
		}
	}
}
