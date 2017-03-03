#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdio.h> 

void rewriter80part2(int a);
void rewriter72part2(int a);
void PlayerChouse2(int Cur);

void MoveToMenu();
void MoveToMenu2();
void MoveToMenu3();

enum COLOR {
	GREEN_COLOR = 10, GREEN_COLOR_DARK = 2
};

using namespace std;

HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);

void Stand(int x, int y, int k, char*str) {
	CONSOLE_CURSOR_INFO ci; ci.bVisible = 0; ci.dwSize = 100; SetConsoleCursorInfo(H, &ci); // убрать мигающий курсор
	setlocale(LC_ALL, "RUS");
	COORD c;
	c.X = x; c.Y = y;
	SetConsoleCursorPosition(H, c);
	SetConsoleTextAttribute(H, k);
	cout << str << "\n";
}

void hat()
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
	for (int r = 0; r < rowsCount; r++)
	{
		for (int c = 0; c < columnsCount; c++)
		{

			cout << levelData[r][c];
		}
		printf("\n\t");

	}

}

void punkt()
{
	hat();
	Stand(30, 9, GREEN_COLOR, "Start game");
	Stand(30, 11, GREEN_COLOR_DARK, "Records");
	Stand(30, 13, GREEN_COLOR_DARK, "Exit");
}

void punkt2()
{
	hat();
	Stand(30, 9, GREEN_COLOR, "Random level");
	Stand(30, 11, GREEN_COLOR_DARK, "Level 1");
	Stand(30, 13, GREEN_COLOR_DARK, "Level 2");
	Stand(30, 15, GREEN_COLOR_DARK, "Level 3");
	Stand(30, 17, GREEN_COLOR_DARK, "Level 4");
	Stand(30, 19, GREEN_COLOR_DARK, "Level 5");
	Stand(30, 21, GREEN_COLOR_DARK, "Back");
}

void punkt3()
{
	hat();
	Stand(30, 9, GREEN_COLOR, "Show all records");
	Stand(30, 11, GREEN_COLOR_DARK, "Show 10 records");
	Stand(30, 13, GREEN_COLOR_DARK, "Back");

}

void rewriter80(int a)
{
	switch (a)
	{
	case 2:
		Stand(30, 9, GREEN_COLOR_DARK, "Start game");
		Stand(30, 11, GREEN_COLOR, "Records");
		break;
	case 3:
		Stand(30, 11, GREEN_COLOR_DARK, "Records");
		Stand(30, 13, GREEN_COLOR, "Exit");
		break;
	}

}

void rewriter80part2(int a)
{
	switch (a)
	{
	case 2:
		Stand(30, 9, GREEN_COLOR_DARK, "Random level");
		Stand(30, 11, GREEN_COLOR, "Level 1");

		break;

	case 3:
		Stand(30, 11, GREEN_COLOR_DARK, "Level 1");
		Stand(30, 13, GREEN_COLOR, "Level 2");

		break;

	case 4:
		Stand(30, 13, GREEN_COLOR_DARK, "Level 2");
		Stand(30, 15, GREEN_COLOR, "Level 3");

		break;

	case 5:
		Stand(30, 15, GREEN_COLOR_DARK, "Level 3");
		Stand(30, 17, GREEN_COLOR, "Level 4");
		break;

	case 6:
		Stand(30, 17, GREEN_COLOR_DARK, "Level 4");
		Stand(30, 19, GREEN_COLOR, "Level 5");
		break;

	case 7:
		Stand(30, 19, GREEN_COLOR_DARK, "Level 5");
		Stand(30, 21, GREEN_COLOR, "Back");
		break;
	}

}

void rewriter80part3(int a)
{
	switch (a)
	{
	case 2:
		Stand(30, 9, GREEN_COLOR_DARK, "Show all records");
		Stand(30, 11, GREEN_COLOR, "Show 10 records");
		break;
	case 3:
		Stand(30, 11, GREEN_COLOR_DARK, "Show 10 records");
		Stand(30, 13, GREEN_COLOR, "Back");
		break;
	}
}

void rewriter72(int a)
{
	switch (a)
	{
	case 1:
		Stand(30, 9, GREEN_COLOR, "Start game");
		Stand(30, 11, GREEN_COLOR_DARK, "Records");
		break;
	case 2:
		Stand(30, 11, GREEN_COLOR, "Records");
		Stand(30, 13, GREEN_COLOR_DARK, "Exit");
		break;
	case 3:
		Stand(30, 13, GREEN_COLOR, "Exit");
		break;
	}
}

void rewriter72part2(int a)
{
	switch (a)
	{
	case 1:
		Stand(30, 9, GREEN_COLOR, "Random level");
		Stand(30, 11, GREEN_COLOR_DARK, "Level 1");
		break;
	case 2:
		Stand(30, 11, GREEN_COLOR, "Level 1");
		Stand(30, 13, GREEN_COLOR_DARK, "Level 2");
		break;

	case 3:
		Stand(30, 13, GREEN_COLOR, "Level 2");
		Stand(30, 15, GREEN_COLOR_DARK, "Level 3");
		break;

	case 4:
		Stand(30, 15, GREEN_COLOR, "Level 3");
		Stand(30, 17, GREEN_COLOR_DARK, "Level 4");
		break;

	case 5:
		Stand(30, 17, GREEN_COLOR, "Level 4");
		Stand(30, 19, GREEN_COLOR_DARK, "Level 5");
		break;

	case 6:
		Stand(30, 19, 10, "Level 5");
		Stand(30, 21, GREEN_COLOR_DARK, "Back");
		break;
	}
}

void rewriter72part3(int a)
{
	switch (a)
	{
	case 1:
		Stand(30, 9, GREEN_COLOR, "Show all records");
		Stand(30, 11, GREEN_COLOR_DARK, "Show 10 records");
		break;
	case 2:
		Stand(30, 11, GREEN_COLOR, "Show 10 records");
		Stand(30, 13, GREEN_COLOR_DARK, "Back");
		break;
	case 3:
		Stand(30, 13, GREEN_COLOR, "Back");
		break;
	}
}

// присоединять свои функции только в функциях PlayerChose2 и PlayerChose3, вместо соответствующих текстовых сообщений

void PlayerChouse(int Cur)
{
	system("cls");
	switch (Cur)
	{
	case 1: punkt2();
		MoveToMenu2();
		break;
	case 2:punkt3();
		MoveToMenu3();
		break;
	case 3: exit(0);
		break;
	}
}

void PlayerChouse3(int Cur)
{
	system("cls");
	switch (Cur)
	{
	case 1: cout << "All Records";
		break;
	case 2:cout << "10 Records";
		break;
	case 3:
		punkt();
		MoveToMenu();;
		break;
	}
}

void PlayerChouse2(int Cur)
{
	system("cls");
	switch (Cur)
	{
	case 1: cout << "Random level";
		break;
	case 2:cout << "Level 1";
		break;
	case 3:cout << "Level 2";
		break;
	case 4:cout << "Level 3";
		break;
	case 5:cout << "Level 4";
		break;
	case 6:cout << "Level 5";
		break;
	case 7:
		punkt();
		MoveToMenu();;
		break;
	}
}


void MoveToMenu()
{
	int position = 1;

	while (1)
	{
		int code = _getch();
		switch (code)
		{
		case 80:
			if (position < 3)
				position++;
			rewriter80(position);
			break;

		case 72:
			if (position > 1)
				position--;
			rewriter72(position);
			break;

		case 13://вниз
			PlayerChouse(position);
			break;
		}
	}
}

void MoveToMenu2()
{
	int position = 1;

	while (1)
	{
		int code = _getch();
		switch (code)
		{
		case 80:
			if (position < 7)
				position++;
			rewriter80part2(position);
			break;

		case 72:
			if (position > 1)
				position--;
			rewriter72part2(position);
			break;

		case 13:
			PlayerChouse2(position);
			break;
		}
	}
}
void MoveToMenu3()
{
	int position = 1;

	while (1)
	{
		int code = _getch();
		switch (code)
		{
		case 80:
			if (position < 3)
				position++;
			rewriter80part3(position);
			break;

		case 72:
			if (position > 1)
				position--;
			rewriter72part3(position);
			break;

		case 13:
			PlayerChouse3(position);
			break;
		}
	}
}


//////////////////////////////////////////////////////////// вызывать в  main только функции: punkt(); и MoveToMenu();


