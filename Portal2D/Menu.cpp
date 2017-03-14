#include "Menu.h"
#include "Tree.h"

HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);

//------Print Functions------//
//Рисует логотип
void menu::drawLogo()
{
	cout << "\t\t\t\t***   **** ***  ***  *   *     ***  ***   " << endl;
	cout << "\t\t\t\t*  *  *  * *  *  *  * *  *       *  *  *  " << endl;
	cout << "\t\t\t\t***   *  * * *   * * * * *     * *  *  *  " << endl;
	cout << "\t\t\t\t*     *  * *  *  * *   * *     *    *  *  " << endl;
	cout << "\t\t\t\t*     **** *  *  * *   * ***   ***  ***   " << endl;
	cout << "\n\n\n";
}

//Выводит вариант меню, на котором остановился пользователь в пункте Records
void menu::printPointRecord(int key)
{
	drawLogo();																			// Рисуем лого

	/* В зависимости от того, на каком пункте остановился пользователь,
	рисуем меню*/
	switch (key)
	{
	case Search:
		cout << "\t\t\t\t\t<<     Search         >>" << endl;
		cout << "\t\t\t\t\t    Show All Records    " << endl;
		cout << "\t\t\t\t\t    Show 10 Records     " << endl;
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

//Выводит вариант главного меню, на котором остановился пользователь
void menu::printMenu(int key)
{
	drawLogo();																			// Рисуем лого

	/* В зависимости от того, на каком пункте остановился пользователь,
	рисуем меню*/
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

//Выводит вариант меню, на котором остановился пользователь в пункте Start
void menu::printPointStart(int key)
{
	//game::clearScreen();
	system("cls");
	drawLogo();																			// Рисуем лого

	/*В зависимости от того, на каком пункте остановился пользователь,
		рисуем меню*/
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
//Воспроизводит выбранный пользователем пункт в разделе Records
void menu::doPointRecords()
{
	int key = Search;																	// Пункт на котором остановился пользователь

	/*Верхняя граница равна Search, нижняя равна BackRecords,
	вывод данного подпункта меню осуществляет printPointRecord*/
	ParametersForMenu parametersForMenu = { Search, BackRecords, &printPointRecord };	

	/*Пока пользователь не захочет выйти из этого подпункта меню,
	осуществляется перемещения по меню*/
	do
	{
		key = controlMenu(parametersForMenu);											// key получает значение пункта на котором остановился пользователь и нажал Enter
		system("cls");

		/*Заходим в раздел который выбрал пользователь*/
		switch (key)
		{

		case Search:
			break;

		case ShowAllRecords:
			break;

		case Show10Records:
			break;

		default:
			break;
		}
	} while (key != BackRecords);

	system("cls");
}

//Воспроизводит выбранный пользователем пункт в разделе Start
void menu::doPointStart()
{
	int key = Instruction;																// Пункт на котором остановился пользователь

	/*Верхняя граница равна Instruction, нижняя равна BackLevel,
	вывод данного подпункта меню осуществляет printPointStart*/
	ParametersForMenu parametersForMenu = { Instruction, BackLevel, &printPointStart };

	/*Пока пользователь не захочет выйти из этого подпункта меню,
	осуществляется перемещения по меню*/
	do
	{
		key = controlMenu(parametersForMenu);											// key получает значение пункта на котором остановился пользователь и нажал Enter
		system("cls");

		/*Заходим в раздел который выбрал пользователь*/
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

//Реализует управление меню и его вывод на экран
int menu::controlMenu(ParametersForMenu parametersForMenu)
{
	int key = parametersForMenu.upBorder;													// key равен самому верхнему пункту меню
	int press;																				// Нажатие пользователя
	game::clearScreen();
	parametersForMenu.print(key);															// Выводит нужный вариант меню
	press = _getch();																		// Принимает значение нажатой клавиши

	/*Если нажата стрелочка, то проверяем какая*/
	if (press == ARROWS)
	{
		/*Пока не нажат Enter перемещаемся по меню*/
		while (press != ENTER)
		{
			press = _getch();																// Примаем значение стрелочки

			/*Если нажата стрелочка вниз, то спускаемся на пункт ниже
			  Если нажата стрелочка вверх, то поднимаемся на пункт вверх*/
			switch (press)
			{
			case UP_ARROW:

				/*Если пользователь не достиг верхнего пункта меню,
				то поднимаемся на пункт выше*/
				if (key != parametersForMenu.upBorder)
					key -= 1;
				break;

			case DOWN_ARROW:

				/*Если пользователь не достиг нижнего пункта меню,
					то спускаемся на пункт ниже*/
				if (key != parametersForMenu.lowerBorder)
					key += 1;
				break;
			}
			game::clearScreen();
			parametersForMenu.print(key);													// Выводит нужный вариант меню
		}
	}
	game::clearScreen();
	return key;																				// Возвращаем выбор пользователя
}

//Воспроизводит выбранный пользователем пункт в главном меню
void menu::menu()
{
	int key;
	/*Верхняя граница равна Start, нижняя равна Exit,
	вывод данного подпункта меню осуществляет printMenu*/
	ParametersForMenu borders = { Start, Exit, &printMenu };

	/*Пока пользователь не захочет выйти из этого подпункта меню,
	осуществляется перемещения по меню*/
	do
	{
		key = controlMenu(borders);															// key получает значение пункта на котором остановился пользователь и нажал Enter

		/*После нажатия кнопки Enter, заходим в пункт который был выбран*/
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