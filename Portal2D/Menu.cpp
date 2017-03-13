#include "Menu.h"
#include "Tree.h"
#include "Search.h"

HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);

void stand(int X_COORD, int Y_COORD, int TEXT_COLOR, char*str)
{
	CONSOLE_CURSOR_INFO ci;
	ci.bVisible = 0;
	ci.dwSize = 100;
	SetConsoleCursorInfo(H, &ci);
	COORD c;
	c.X = X_COORD; c.Y = Y_COORD;
	SetConsoleCursorPosition(H, c);
	SetConsoleTextAttribute(H, TEXT_COLOR);

	if (str == "Level 1" &&  TEXT_COLOR == 10)
	{
		cout << str << " ";
		records::giveBestPlayerInLevel(1);
	}
	else if (str == "Level 2" &&  TEXT_COLOR == 10)
	{
		cout << str << " ";
		records::giveBestPlayerInLevel(2);
	}
	else if (str == "Level 3" &&  TEXT_COLOR == 10)
	{
		cout << str << " ";
		records::giveBestPlayerInLevel(3);
	}
	else if (str == "Level 4" &&  TEXT_COLOR == 10)
	{
		cout << str << " ";
		records::giveBestPlayerInLevel(4);
	}
	else if (str == "Level 5" &&  TEXT_COLOR == 10)
	{
		cout << str << " ";
		records::giveBestPlayerInLevel(5);
	}
	else
	{
		cout << str << "\n";
	}
}

void hat()
{
	const int rowsCount = 5;
	const int columnsCount = 55;
	const unsigned char levelData[rowsCount][columnsCount + 1] =
	{
		//?????????? ???????-?????
		"           ***   **** ***  ***  *   *     ***  ***   ",
		"           *  *  *  * *  *  *  * *  *       *  *  *  ",
		"           ***   *  * * *   * * * * *     * *  *  *  ",
		"           *     *  * *  *  * *   * *     *    *  *  ",
		"           *     **** *  *  * *   * ***   ***  ***   ",

	};
	cout << "\t";
	for (int r = 0; r <rowsCount; r++)
	{
		for (int c = 0; c < columnsCount; c++)
		{

			cout << levelData[r][c];
		}
		cout << "\n\t";

	}

}

void pointToMenu()
{
	//system("color 3F");
	hat();
	stand(30, 9, LightGreen, "Start game");
	stand(30, 11, DarkGreen, "Records");
	stand(30, 13, DarkGreen, "Exit");
}
void pointToMenu2()
{
	//system("color 3F");
	hat();
	stand(30, 9, LightGreen, "Instruction");
	stand(30, 11, DarkGreen, "Random level");
	stand(30, 13, DarkGreen, "Level 1");
	stand(30, 15, DarkGreen, "Level 2");
	stand(30, 17, DarkGreen, "Level 3");
	stand(30, 19, DarkGreen, "Level 4");
	stand(30, 21, DarkGreen, "Level 5");
	stand(30, 23, DarkGreen, "Back");
}
void pointToMenu3()
{
	//system("color 3F");
	hat();
	stand(30, 9, LightGreen, "Search");
	stand(30, 11, DarkGreen, "Show all records");
	stand(30, 13, DarkGreen, "Show 10 records");
	stand(30, 15, DarkGreen, "Back");

}


void rewriterCaseDownPoint(int a)
{
	switch (a)
	{
	case 2:
		stand(30, 9, DarkGreen, "Start game");
		stand(30, 11, LightGreen, "Records");
		break;
	case 3:
		stand(30, 11, DarkGreen, "Records");
		stand(30, 13, LightGreen, "Exit");
		break;
	}

}
void rewriterCaseDownPoint2(int a)
{
	switch (a)
	{
	case 2:
		stand(30, 9, DarkGreen, "Instruction");
		stand(30, 11, LightGreen, "Random level");

		break;

	case 3:
		stand(30, 11, DarkGreen, "Random level");
		stand(30, 13, LightGreen, "Level 1");

		stand(38, 15, LightGreen, "                                          ");
		stand(38, 17, LightGreen, "                                          ");
		stand(38, 19, LightGreen, "                                          ");
		stand(38, 21, LightGreen, "                                          ");



		break;

	case 4:
		stand(30, 13, DarkGreen, "Level 1");
		stand(30, 15, LightGreen, "Level 2");

		stand(38, 13, LightGreen, "                                          ");
		stand(38, 17, LightGreen, "                                          ");
		stand(38, 19, LightGreen, "                                          ");
		stand(38, 21, LightGreen, "                                          ");


		break;

	case 5:
		stand(30, 15, DarkGreen, "Level 2");
		stand(30, 17, LightGreen, "Level 3");

		stand(38, 15, LightGreen, "                                          ");
		stand(38, 13, LightGreen, "                                          ");
		stand(38, 19, LightGreen, "                                          ");
		stand(38, 21, LightGreen, "                                          ");

		break;

	case 6:
		stand(30, 17, DarkGreen, "Level 3");
		stand(30, 19, LightGreen, "Level 4");

		stand(38, 15, LightGreen, "                                          ");
		stand(38, 13, LightGreen, "                                          ");
		stand(38, 17, LightGreen, "                                          ");
		stand(38, 21, LightGreen, "                                          ");

		break;

	case 7:
		stand(30, 19, DarkGreen, "Level 4");
		stand(30, 21, LightGreen, "Level 5");

		stand(38, 15, LightGreen, "                                          ");
		stand(38, 13, LightGreen, "                                          ");
		stand(38, 17, LightGreen, "                                          ");
		stand(38, 19, LightGreen, "                                          ");

		break;
	case 8:
		stand(30, 21, DarkGreen, "Level 5");
		stand(30, 23, LightGreen, "Back");

		stand(38, 21, LightGreen, "                                          ");

		break;
	}

}
void rewriterCaseDownPoint3(int a)
{
	switch (a)
	{
	case 2:
		stand(30, 9, DarkGreen, "Search");
		stand(30, 11, LightGreen, "Show all records");
		break;
	case 3:
		stand(30, 11, DarkGreen, "Show all records");
		stand(30, 13, LightGreen, "Show 10 records");
		break;
	case 4:
		stand(30, 13, DarkGreen, "Show 10 records");
		stand(30, 15, LightGreen, "Back");
		break;
	}

}


void rewriterCaseUpPoint(int a)
{
	switch (a)
	{

	case 1:
		stand(30, 9, LightGreen, "Start game");
		stand(30, 11, DarkGreen, "Records");
		break;
	case 2:
		stand(30, 11, LightGreen, "Records");
		stand(30, 13, DarkGreen, "Exit");
		break;
	case 3:
		stand(30, 13, LightGreen, "Exit");
		break;
	}

}
void rewriterCaseUpPoint2(int a)
{
	switch (a)
	{

	case 1:
		stand(30, 9, LightGreen, "Instruction");
		stand(30, 11, DarkGreen, "Random level");



		break;
	case 2:
		stand(38, 13, LightGreen, "                                          ");
		stand(30, 11, LightGreen, "Random level");
		stand(30, 13, DarkGreen, "Level 1");


		break;

	case 3:
		stand(30, 13, LightGreen, "Level 1");
		stand(30, 15, DarkGreen, "Level 2");
		stand(38, 15, LightGreen, "                                          ");
		stand(38, 17, LightGreen, "                                          ");
		stand(38, 19, LightGreen, "                                          ");
		stand(38, 21, LightGreen, "                                          ");
		break;

	case 4:
		stand(30, 15, LightGreen, "Level 2");
		stand(30, 17, DarkGreen, "Level 3");

		stand(38, 13, LightGreen, "                                          ");
		stand(38, 17, LightGreen, "                                          ");
		stand(38, 19, LightGreen, "                                          ");
		stand(38, 21, LightGreen, "                                          ");
		break;

	case 5:
		stand(30, 17, LightGreen, "Level 3");
		stand(30, 19, DarkGreen, "Level 4");

		stand(38, 15, LightGreen, "                                          ");
		stand(38, 13, LightGreen, "                                          ");
		stand(38, 19, LightGreen, "                                          ");
		stand(38, 21, LightGreen, "                                          ");



		break;

	case 6:
		stand(30, 19, LightGreen, "Level 4");
		stand(30, 21, DarkGreen, "Level 5");
		stand(38, 15, LightGreen, "                                          ");
		stand(38, 13, LightGreen, "                                          ");
		stand(38, 17, LightGreen, "                                          ");
		stand(38, 21, LightGreen, "                                          ");



		break;
	case 7:
		stand(30, 21, LightGreen, "Level 5");
		stand(30, 23, DarkGreen, "Back");
		break;


	}
}
void rewriterCaseUpPoint3(int a)
{
	switch (a)
	{

	case 1:
		stand(30, 9, LightGreen, "Search");
		stand(30, 11, DarkGreen, "Show all records");
		break;
	case 2:
		stand(30, 11, LightGreen, "Show all records");
		stand(30, 13, DarkGreen, "Show 10 records");
		break;
	case 3:
		stand(30, 13, LightGreen, "Show 10 records");
		stand(30, 15, DarkGreen, "Back");
		break;
	case 4:
		stand(30, 15, LightGreen, "Back");

		break;
		break;
	}

}


// ???????????? ???? ??????? ?????? ? ???????? userSelection2 ? userSelection3, ?????? ??????????????? ????????? ?????????
void userSelection(int Cur)
{
	system("cls");
	switch (Cur)
	{

	case 1:pointToMenu2();
		moveToMenuPoint2();
		break;
	case 2:pointToMenu3();
		moveToMenuPoint3();
		break;
	case 3:;

		break;
	}
}
void userSelection2(int Cur)
{
	system("cls");
	switch (Cur)
	{

	case 1:
		//game::showInstruction();
		_getch();
		system("cls");
		pointToMenu2();
		moveToMenuPoint2();

		break;
	case 2:cout << "Random level";


		_getch();
		break;
	case 3:
		SetConsoleTextAttribute(H, LightGrey);
		game::startLevel("Lvl_1.txt");
		//_getch();
		break;
	case 4:cout << "Level 2";
		_getch();
		break;
	case 5:cout << "Level 3";
		_getch();
		break;
	case 6:cout << "Level 4";
		_getch();
		break;
	case 7:cout << "Level 5";
		_getch();
		break;
	case 8:
		pointToMenu();
		moveToMenuPoint();;
		break;
	}
}
void userSelection3(int Cur)
{
	system("cls");
	records::DataAboutTheChampion empty;
	int parametr = 0;
	char *symbol = new char[1];
	switch (Cur)
	{

	case 1: 
		cout << "\tenter 1 - if you want to search by score parameter, 2 - level parameter, 3 - name parameter " << std::endl;
		symbol[0] = _getch();
		parametr = atoi(symbol);
		search::setSearchParametr(parametr);
		system("cls");
		pointToMenu3();
		moveToMenuPoint3();
		break;

	case 2:cout << "All Records";
		records::addInRecordsOrShowRecords(empty, "show");
		cout << "smth2";
		_getch();
		system("cls");
		pointToMenu3();
		moveToMenuPoint3();
		break;
	case 3:cout << "10 Records";
		records::addInRecordsOrShowRecords(empty, "show10");
		cout << "smth3";
		_getch();
		system("cls");
		pointToMenu3();
		moveToMenuPoint3();
		break;
	case 4:
		pointToMenu();
		moveToMenuPoint();;
		break;
	}
	delete[] symbol;
}


void moveToMenuPoint()
{
	bool f = true;
	int position = 1;

	while (f == true) {
		int code = _getch();
		switch (code)
		{
		case DOWN_ARROW:
			if (position<3)
				position++;
			rewriterCaseDownPoint(position);

			break;
		case UP_ARROW:
			if (position>1)

				position--;
			rewriterCaseUpPoint(position);

			break;
		case ENTER://????

			userSelection(position);
			f = false;
			break;
		}
	}
}
void moveToMenuPoint2()
{
	bool f = true;
	int position = 1;

	while (f == true) {
		int code = _getch();
		switch (code)
		{
		case DOWN_ARROW:
			if (position<8)
				position++;
			rewriterCaseDownPoint2(position);

			break;
		case UP_ARROW:
			if (position>1)

				position--;
			rewriterCaseUpPoint2(position);

			break;
		case ENTER:
			userSelection2(position);
			f = false;

			break;
		}
	}
}
void moveToMenuPoint3()
{
	bool f = true;
	int position = 1;

	while (f == true) {
		int code = _getch();
		switch (code)
		{
		case DOWN_ARROW:
			if (position<4)
				position++;
			rewriterCaseDownPoint3(position);

			break;
		case UP_ARROW:
			if (position>1)

				position--;
			rewriterCaseUpPoint3(position);

			break;
		case ENTER:

			userSelection3(position);
			f = false;
			break;
		}
	}
}