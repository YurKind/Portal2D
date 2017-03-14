#include "Menu.h"
#include "Tree.h"

HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);

//------Print Functions------//
//–исует логотип
void menu::drawLogo()
{
	cout << "\t\t\t\t***   **** ***  ***  *   *     ***  ***   " << endl;
	cout << "\t\t\t\t*  *  *  * *  *  *  * *  *       *  *  *  " << endl;
	cout << "\t\t\t\t***   *  * * *   * * * * *     * *  *  *  " << endl;
	cout << "\t\t\t\t*     *  * *  *  * *   * *     *    *  *  " << endl;
	cout << "\t\t\t\t*     **** *  *  * *   * ***   ***  ***   " << endl;
	cout << "\n\n\n";
}

//¬ыводит вариант меню, на котором остановилс€ пользователь в пункте Records
void menu::printPointRecord(int key)
{
	drawLogo();

	switch (key)
	{
	case Search:
		cout << "\t\t\t\t\t<<     Search         >>" << endl;
		cout << "\t\t\t\t\t    Show All Records    " << endl;
		cout << "\t\t\t\t\t    Show 10 Records     " << endl;
		cout << "\t\t\t\t\t    Best Of The Best    " << endl;
		cout << "\t\t\t\t\t       Back             " << endl;
		break;

	case ShowAllRecords:
		cout << "\t\t\t\t\t       Search           " << endl;
		cout << "\t\t\t\t\t<<  Show All Records  >>" << endl;
		cout << "\t\t\t\t\t    Show 10 Records     " << endl;
		cout << "\t\t\t\t\t       Back             " << endl;
		break;

	case Show10Records:
		cout << "\t\t\t\t\t       Search           " << endl;
		cout << "\t\t\t\t\t    Show All Records    " << endl;
		cout << "\t\t\t\t\t<<  Show 10 Records   >>" << endl;
		cout << "\t\t\t\t\t       Back             " << endl;
		break;

	case BackRecords:
		cout << "\t\t\t\t\t       Search           " << endl;
		cout << "\t\t\t\t\t    Show All Records    " << endl;
		cout << "\t\t\t\t\t    Show 10 Records     " << endl;
		cout << "\t\t\t\t\t<<     Back           >>" << endl;
		break;
	}
}

//¬ыводит вариант главного меню, на котором остановилс€ пользователь
void menu::printMenu(int key)
{
	drawLogo();

	switch (key)
	{
	case Start:
		cout << "\t\t\t\t\t<<  Start  >>" << endl;
		cout << "\t\t\t\t\t   Records   " << endl;
		cout << "\t\t\t\t\t    Exit     " << endl;
		break;
	case Records:
		cout << "\t\t\t\t\t    Start    " << endl;
		cout << "\t\t\t\t\t<< Records >>" << endl;
		cout << "\t\t\t\t\t    Exit     " << endl;
		break;
	case Exit:
		cout << "\t\t\t\t\t    Start    " << endl;
		cout << "\t\t\t\t\t   Records   " << endl;
		cout << "\t\t\t\t\t<<  Exit   >>" << endl;
		break;
	}
}

//¬ыводит вариант меню, на котором остановилс€ пользователь в пункте Start
void menu::printPointStart(int key)
{
	system("cls");
	drawLogo();

	switch (key)
	{
	case Instruction:
		cout << "\t\t\t\t\t<<  Instruction  >>" << endl;
		cout << "\t\t\t\t\t    Random Level   " << endl;
		cout << "\t\t\t\t\t      Level 1      " << endl;
		cout << "\t\t\t\t\t      Level 2      " << endl;
		cout << "\t\t\t\t\t      Back         " << endl;
		break;

	case RandomLevel:
		cout << "\t\t\t\t\t    Instruction    " << endl;
		cout << "\t\t\t\t\t<<  Random Level >>" << endl;
		cout << "\t\t\t\t\t      Level 1      " << endl;
		cout << "\t\t\t\t\t      Level 2      " << endl;
		cout << "\t\t\t\t\t      Back         " << endl;
		break;

	case Level1:
		cout << "\t\t\t\t\t    Instruction    " << endl;
		cout << "\t\t\t\t\t    Random Level   " << endl;
		cout << "\t\t\t\t\t<<    Level 1    >>"; records::giveBestPlayerInLevel(1);
		cout << "\t\t\t\t\t      Level 2      " << endl;
		cout << "\t\t\t\t\t      Back         " << endl;
		break;

	case Level2:
		cout << "\t\t\t\t\t    Instruction    " << endl;
		cout << "\t\t\t\t\t    Random Level   " << endl;
		cout << "\t\t\t\t\t      Level 1      " << endl;
		cout << "\t\t\t\t\t<<    Level 2    >>"; records::giveBestPlayerInLevel(2);
		cout << "\t\t\t\t\t      Back         " << endl;
		break;

	case BackLevel:
		cout << "\t\t\t\t\t    Instruction    " << endl;
		cout << "\t\t\t\t\t    Random Level   " << endl;
		cout << "\t\t\t\t\t      Level 1      " << endl;
		cout << "\t\t\t\t\t      Level 2      " << endl;
		cout << "\t\t\t\t\t<<    Back       >>" << endl;
		break;
	}

}

//------Control Functions------//
//¬оспроизводит выбранный пользователем пункт в разделе Records
void menu::doPointRecords()
{
	int key;
	ParametersForMenu parametersForMenu = { Search, BackRecords, &printPointRecord };

	do
	{
		key = controlMenu(parametersForMenu);
		game::clearScreen();
		switch (key)
		{
		case Search:
			break;

		case ShowAllRecords:
			break;

		case Show10Records:
			break;

		case BestOfTheBest:
			break;

		default:
			break;
		}
	} while (key != BackRecords);

	system("cls");
}

//¬оспроизводит выбранный пользователем пункт в разделе Start
void menu::doPointStart()
{
	int key;
	ParametersForMenu name = { Instruction, BackLevel, &printPointStart };

	do
	{
		key = controlMenu(name);//!!!!!!!!!
		system("cls");
		switch (key)
		{

		case Instruction:
			game::showInstruction();
			break;

		case RandomLevel:
			system("pause");
			break;

		case Level1:
			game::startLevel("Lvl_1.txt");
			break;

		case Level2:
			system("pause");
			break;

		default:
			break;
		}
	} while (key != BackLevel);

	system("cls");
}

//–еализует управление меню и его вывод на экран
int menu::controlMenu(ParametersForMenu borders)
{
	int key = borders.upBorder;
	int press;
	game::clearScreen();
	borders.print(key);
	//printFunc(key);
	press = _getch();
	if (press == ARROWS)
	{
		while (press != ENTER)
		{
			press = _getch();

			switch (press)
			{
			case UP_ARROW:
				if (key != borders.upBorder)
					key -= 1;
				break;

			case DOWN_ARROW:
				if (key != borders.lowerBorder)
					key += 1;
				break;
			}
			game::clearScreen();
			borders.print(key);
		}
	}
	game::clearScreen();
	return key;
}

//¬оспроизводит выбранный пользователем пункт в главном меню
void menu::menu()
{
	int key;
	ParametersForMenu borders = { Start, Exit, &printMenu };
	do
	{
		key = controlMenu(borders);

		/*ѕосле нажати€ кнопки Enter, заходим в пункт который был выбран*/
		switch (key)
		{
		case Start:
			doPointStart();
			break;

		case Records:
			doPointRecords();
			break;

		default:
			break;
		}
	} while (key != Exit);
}