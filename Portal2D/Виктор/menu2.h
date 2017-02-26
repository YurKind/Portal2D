#pragma once
#include <iostream>
#include <windows.h>
#include <conio.h>
#include "stand.h"
#include "menu1.h"

using namespace std;


void menu2()
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

	Stand(30, 9, 10, "Random level");
	Stand(30, 11, 2, "Level 1");
	Stand(30, 13, 2, "Level 2");
	Stand(30, 15, 2, "Level 3");
	Stand(30, 17, 2, "Level 4");
	Stand(30, 19, 2, "Level 5");
	Stand(30, 21, 2, "Back");

	int k; // код клавиши
	int cur = 1; // какой пункт выбран сейчас
	while (1){
		k = _getch();
		if (k == 80){
			if (cur<7){
				cur++;
				if (cur == 2){
					Stand(30, 9, 2, "Random level");
					Stand(30, 11, 10, "Level 1");
				}
				else if (cur == 3){
					Stand(30, 11, 2, "Level 1");
					Stand(30, 13, 10, "Level 2");
				}
				else if (cur == 4){
					Stand(30, 13, 2, "Level 2");
					Stand(30, 15, 10, "Level 3");
				}
				else if (cur == 5){
					Stand(30, 15, 2, "Level 3");
					Stand(30, 17, 10, "Level 4");
				}
				else if (cur == 6){
					Stand(30, 17, 2, "Level 4");
					Stand(30, 19, 10, "Level 5");
				}
				else if (cur == 7){
					Stand(30, 19, 2, "Level 5");
					Stand(30, 21, 10, "Back");
				}

			}
		}
		else if (k == 72){
			if (cur>1){
				cur--;
				if (cur == 6){
					Stand(30, 19, 10, "Level 5");
					Stand(30, 21, 2, "Back");

				}
				if (cur == 5){
					Stand(30, 17, 10, "Level 4");
					Stand(30, 19, 2, "Level 5");

				}
				if (cur == 4){
					Stand(30, 15, 10, "Level 3");
					Stand(30, 17, 2, "Level 4");

				}
				if (cur == 3){
					Stand(30, 13, 10, "Level 2");
					Stand(30, 15, 2, "Level 3");

				}
				else if (cur == 2){
					Stand(30, 11, 10, "Level 1");
					Stand(30, 13, 2, "Level 2");
				}
				else if (cur == 1){
					Stand(30, 9, 10, "Random level");
					Stand(30, 11, 2, "Level 1");
				}
			}
		}
		else if (k == 13){
			system("cls");
			SetConsoleTextAttribute(H, 12);
			if (cur == 1) cout << "Рандом!\n\n";
			else if (cur == 2) cout << "уровень 1!\n\n";
			else if (cur == 3) cout << "уровень 2!\n\n";
			else if (cur == 4) cout << "уровень 3!\n\n";
			else if (cur == 5) cout << "уровень 4!\n\n";
			else if (cur == 6) cout << "уровень 5!\n\n";


			else  menu2();
			_getch();
			exit(0);
		}
	}
}
