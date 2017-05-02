#include "Menu.h"
#include "Gameplay.h"
#include "Search.h"
#include "RandomLevel.h"
#include "List.h"

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
		cout << "\t\t\t\t\t<<      Search        >>" << endl;
		cout << "\t\t\t\t\t    Show All Records    " << endl;
		cout << "\t\t\t\t\t    Best Of The Best    " << endl;
		cout << "\t\t\t\t\t         Back           " << endl;
		break;

	case ShowAllRecords:
		cout << "\t\t\t\t\t        Search          " << endl;
		cout << "\t\t\t\t\t<<  Show All Records  >>" << endl;
		cout << "\t\t\t\t\t    Best Of The Best    " << endl;
		cout << "\t\t\t\t\t         Back           " << endl;
		break;

	case BestOfTheBest:
		cout << "\t\t\t\t\t        Search          " << endl;
		cout << "\t\t\t\t\t    Show All Records    " << endl;
		cout << "\t\t\t\t\t<<  Best Of The Best  >>" << endl;
		cout << "\t\t\t\t\t         Back           " << endl;
		break;

	case BackRecords:
		cout << "\t\t\t\t\t        Search          " << endl;
		cout << "\t\t\t\t\t    Show All Records    " << endl;
		cout << "\t\t\t\t\t    Best Of The Best    " << endl;
		cout << "\t\t\t\t\t<<       Back         >>" << endl;
		break;
	}
}

void menu::printPointSearch(int key)
{
	drawLogo();

	switch (key)
	{
	case ByScore:
		cout << "\t\t\t\t\t<<   Search By Score   >>" << endl;
		cout << "\t\t\t\t\t     Search By Level     " << endl;
		cout << "\t\t\t\t\t     Search By Name      " << endl;
		cout << "\t\t\t\t\t   Search By Substring   " << endl;
		cout << "\t\t\t\t\t          Back           " << endl;
		break;

	case ByLevel:
		cout << "\t\t\t\t\t     Search By Score     " << endl;
		cout << "\t\t\t\t\t<<   Search By Level   >>" << endl;
		cout << "\t\t\t\t\t     Search By Name      " << endl;
		cout << "\t\t\t\t\t   Search By Substring   " << endl;
		cout << "\t\t\t\t\t          Back           " << endl;
		break;

	case ByName:
		cout << "\t\t\t\t\t     Search By Score     " << endl;
		cout << "\t\t\t\t\t     Search By Level     " << endl;
		cout << "\t\t\t\t\t<<   Search By Name    >>" << endl;
		cout << "\t\t\t\t\t   Search By Substring   " << endl;
		cout << "\t\t\t\t\t          Back           " << endl;
		break;

	case BySubstring:
		cout << "\t\t\t\t\t     Search By Score     " << endl;
		cout << "\t\t\t\t\t     Search By Level     " << endl;
		cout << "\t\t\t\t\t     Search By Name      " << endl;
		cout << "\t\t\t\t\t<< Search By Substring >>" << endl;
		cout << "\t\t\t\t\t          Back           " << endl;
		break;

	case BackRecordsSearch:
		cout << "\t\t\t\t\t     Search By Score     " << endl;
		cout << "\t\t\t\t\t     Search By Level     " << endl;
		cout << "\t\t\t\t\t     Search By Name      " << endl;
		cout << "\t\t\t\t\t   Search By Substring   " << endl;
		cout << "\t\t\t\t\t<<        Back         >>" << endl;
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
	std::system("cls");
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
		cout << "\t\t\t\t\t      Level 3      " << endl;
		cout << "\t\t\t\t\t      Level 4      " << endl;
		cout << "\t\t\t\t\t      Level 5      " << endl;
		cout << "\t\t\t\t\t       Back        " << endl;
		break;

	case RandomLevel:
		cout << "\t\t\t\t\t    Instruction    " << endl;
		cout << "\t\t\t\t\t<<  Random Level >>" << endl;
		cout << "\t\t\t\t\t      Level 1      " << endl;
		cout << "\t\t\t\t\t      Level 2      " << endl;
		cout << "\t\t\t\t\t      Level 3      " << endl;
		cout << "\t\t\t\t\t      Level 4      " << endl;
		cout << "\t\t\t\t\t      Level 5      " << endl;
		cout << "\t\t\t\t\t       Back        " << endl;
		break;

	case Level1:
		cout << "\t\t\t\t\t    Instruction    " << endl;
		cout << "\t\t\t\t\t    Random Level   " << endl;
		cout << "\t\t\t\t\t<<    Level 1    >>"; records::giveBestPlayerInLevel(1);
		cout << "\t\t\t\t\t      Level 2      " << endl;
		cout << "\t\t\t\t\t      Level 3      " << endl;
		cout << "\t\t\t\t\t      Level 4      " << endl;
		cout << "\t\t\t\t\t      Level 5      " << endl;
		cout << "\t\t\t\t\t       Back        " << endl;
		break;

	case Level2:
		cout << "\t\t\t\t\t    Instruction    " << endl;
		cout << "\t\t\t\t\t    Random Level   " << endl;
		cout << "\t\t\t\t\t      Level 1      " << endl;
		cout << "\t\t\t\t\t<<    Level 2    >>"; records::giveBestPlayerInLevel(2);
		cout << "\t\t\t\t\t      Level 3      " << endl;
		cout << "\t\t\t\t\t      Level 4      " << endl;
		cout << "\t\t\t\t\t      Level 5      " << endl;
		cout << "\t\t\t\t\t       Back        " << endl;
		break;

	case Level3:
		cout << "\t\t\t\t\t    Instruction    " << endl;
		cout << "\t\t\t\t\t    Random Level   " << endl;
		cout << "\t\t\t\t\t      Level 1      " << endl;
		cout << "\t\t\t\t\t      Level 2      " << endl;
		cout << "\t\t\t\t\t<<    Level 3    >>"; records::giveBestPlayerInLevel(3);
		cout << "\t\t\t\t\t      Level 4      " << endl;
		cout << "\t\t\t\t\t      Level 5      " << endl;
		cout << "\t\t\t\t\t       Back        " << endl;
		break;

	case Level4:
		cout << "\t\t\t\t\t    Instruction    " << endl;
		cout << "\t\t\t\t\t    Random Level   " << endl;
		cout << "\t\t\t\t\t      Level 1      " << endl;
		cout << "\t\t\t\t\t      Level 2      " << endl;
		cout << "\t\t\t\t\t      Level 3      " << endl;
		cout << "\t\t\t\t\t<<    Level 4    >>"; records::giveBestPlayerInLevel(4);
		cout << "\t\t\t\t\t      Level 5      " << endl;
		cout << "\t\t\t\t\t       Back        " << endl;
		break;

	case Level5:
		cout << "\t\t\t\t\t    Instruction    " << endl;
		cout << "\t\t\t\t\t    Random Level   " << endl;
		cout << "\t\t\t\t\t      Level 1      " << endl;
		cout << "\t\t\t\t\t      Level 2      " << endl;
		cout << "\t\t\t\t\t      Level 3      " << endl;
		cout << "\t\t\t\t\t      Level 4      " << endl;
		cout << "\t\t\t\t\t<<    Level 5    >>"; records::giveBestPlayerInLevel(5);
		cout << "\t\t\t\t\t       Back        " << endl;
		break;

	case BackLevel:
		cout << "\t\t\t\t\t    Instruction    " << endl;
		cout << "\t\t\t\t\t    Random Level   " << endl;
		cout << "\t\t\t\t\t      Level 1      " << endl;
		cout << "\t\t\t\t\t      Level 2      " << endl;
		cout << "\t\t\t\t\t      Level 3      " << endl;
		cout << "\t\t\t\t\t      Level 4      " << endl;
		cout << "\t\t\t\t\t      Level 5      " << endl;
		cout << "\t\t\t\t\t<<     Back      >>" << endl;
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

		std::system("cls");

		/*Заходим в раздел который выбрал пользователь*/
		switch (key)
		{
		case Search:
			menu::doPointRecordSearch();
			break;

		case ShowAllRecords:
			records::addInRecordsOrShowRecords(NULL, "show");
			break;

		case BestOfTheBest:
			std::cout << "\n\n\t\t\t\t\t Best of the best" << std::endl;
			for (int i = NUMBER_OF_LEVELS; i >= 1; i--)
			{
				std::cout << "\n\t\t\t\t" << (11 - i) << " lvl"; records::giveBestPlayerInLevel(i);
			}
			_getch();
			std::system("cls");
			break;

		default:
			break;
		}
	} while (key != BackRecords);
	std::system("cls");
}

//Воспроизводит выбранный пользователем пункт в разделе Records->Search
void menu::doPointRecordSearch()
{
	int key = ByScore;																	// Пункт на котором остановился пользователь

	/*Верхняя граница равна Search, нижняя равна BackRecords,
	вывод данного подпункта меню осуществляет printPointRecord*/
	ParametersForMenu parametersForMenu = { ByScore, BackRecordsSearch, &printPointSearch };

	/*Пока пользователь не захочет выйти из этого подпункта меню,
	осуществляется перемещения по меню*/
	do
	{
		key = controlMenu(parametersForMenu);											// key получает значение пункта на котором остановился пользователь и нажал Enter
		std::system("cls");

		list::List<records::DataAboutTheChampion> *list = NULL, *printList = NULL;       // список с найденными рекорсдменами 
		tree::BranchForNumber<records::DataAboutTheChampion> *tree = NULL;        // дерево со всеми рекордсменами

		double numberOfScore = 0.0;
		int numberOfLevel = 0;
		char *name = new char[1000];
		bool print = true;

		switch (key)
		{
		case ByScore:
			createTree(&tree, FILE_NAME_RECORDS, ByScore);     // создаем и инициализируем список по очкам
			std::cout << "\n\n\n\t\t\t\tEnter the number of score: ";
			std::cin >> numberOfScore;
			std::cout << "\n";
			list = search::searchAllElements<double>(tree, numberOfScore, search::searchByScoreOfOneResult);       // указатель на список с найденными рекорсдменами 

			while (list)
			{
				list::addBegin(&printList, list->value);
				list = list->next;
			}
			break;

		case ByLevel:
			createTree(&tree, FILE_NAME_RECORDS, ByLevel);     // создаем и инициализируем список по уровням
			std::cout << "\n\n\n\t\t\t\tEnter the number of level: ";
			std::cin >> numberOfLevel;
			std::cout << "\n";
			list = search::searchAllElements<int>(tree, numberOfLevel, search::searchByLevelOfOneResult);       // указатель на список с найденными рекорсдменами 

			while (list)
			{
				list::addBegin(&printList, list->value);
				list = list->next;
			}
			break;

		case ByName:
			createTree(&tree, FILE_NAME_RECORDS, ByName);     // создаем и инициализируем список по именам
			std::cout << "\n\n\n\t\t\t\tEnter the string: ";
			std::cin >> name;
			std::cout << "\n";
			list = search::searchAllElements<char*>(tree, name, search::searchByStringOfOneResult);       // указатель на список с найденными рекорсдменами 

			while (list)
			{
				list::addBegin(&printList, list->value);
				list = list->next;
			}
			break;

		case BySubstring:
			std::cout << "\n\n\n\t\t\t\tEnter the substring: ";
			std::cin >> name;
			std::cout << "\n";
			printList = search::searchBySubstringAllResults(list, name);
			break;

		default:
			print = false;
			break;
		}

		if (print)
		{
			search::printFoundChampions(printList, key);
			system("pause");
		}
		list::freeMemory(list);
		tree::freeMemory(tree);
		delete[] name;
		std::system("cls");

	} while (key != BackRecordsSearch);
}

/* Для RandomLevel */
char* menu::getFileNameFormNumberOfLevel(int numberOfLevel)
{
	char* result;
	switch (numberOfLevel)
	{
	case 1:
		result = "Lvl_1.txt";
		break;

	case 2:
		result = "Lvl_2.txt";
		break;

	case 3:
		result = "Lvl_3.txt";
		break;

	case 4:
		result = "Lvl_4.txt";
		break;

	case 5:
		result = "Lvl_5.txt";
		break;

	default:
		result = "Lvl_4.txt";
		break;
	}

	return result;
}

//Воспроизводит выбранный пользователем пункт в разделе Start
void menu::doPointStart(queue::Queue<int> *queue, bool flag)
{
	int key = Instruction;																// Пункт на котором остановился пользователь
	records::DataAboutTheChampion *newChampion = NULL;

	/*Верхняя граница равна Instruction, нижняя равна BackLevel,
	вывод данного подпункта меню осуществляет printPointStart*/
	ParametersForMenu parametersForMenu = { Instruction, BackLevel, &printPointStart };

	/*Пока пользователь не захочет выйти из этого подпункта меню,
	осуществляется перемещения по меню*/
	do
	{
		key = controlMenu(parametersForMenu);											// key получает значение пункта на котором остановился пользователь и нажал Enter
		std::system("cls");

		int numberOfLevel = 0;
		char* fileNameForRandomLevel = "";

		/*Заходим в раздел который выбрал пользователь*/
		switch (key)
		{
		case Instruction:
			game::showInstruction();
			break;

		case RandomLevel:
			if (queue::checkCurrentSizeOfQueue<int>(*queue) <= 2 && flag)
			{
				queue::freeMemory(queue);
				numberOfLevel = random::initializeQueueAndReturnHead(queue);
			}
			else
			{
				flag = true;
				numberOfLevel = random::initializeQueueAndReturnHead(queue);
			}

			fileNameForRandomLevel = menu::getFileNameFormNumberOfLevel(numberOfLevel);
			newChampion = game::startLevel(fileNameForRandomLevel);
			if (newChampion->isPlayerPassedLevel == true)
			{
				records::addInRecordsOrShowRecords(newChampion, "add");
			}
			break;

		case Level1:
			newChampion = game::startLevel("Lvl_1.txt");
			if (newChampion->isPlayerPassedLevel == true)
			{
				records::addInRecordsOrShowRecords(newChampion, "add");
			}
			break;

		case Level2:
			newChampion = game::startLevel("Lvl_2.txt");
			if (newChampion->isPlayerPassedLevel == true)
			{
				records::addInRecordsOrShowRecords(newChampion, "add");
			}
			break;

		case Level3:
			newChampion = game::startLevel("Lvl_3.txt");
			if (newChampion->isPlayerPassedLevel == true)
			{
				records::addInRecordsOrShowRecords(newChampion, "add");
			}
			break;

		case Level4:
			newChampion = game::startLevel("Lvl_4.txt");
			if (newChampion->isPlayerPassedLevel == true)
			{
				records::addInRecordsOrShowRecords(newChampion, "add");
			}
			break;

		case Level5:
			newChampion = game::startLevel("Lvl_5.txt");
			if (newChampion->isPlayerPassedLevel == true)
			{
				records::addInRecordsOrShowRecords(newChampion, "add");
			}
			break;

		default:
			break;
		}
	} while (key != BackLevel);

	std::system("cls");
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
	return key;																				// Возвращаем выбор пользователя
}

//Воспроизводит выбранный пользователем пункт в главном меню
void menu::menu(queue::Queue<int> *queue, bool flag)
{
	int key;
	/*Верхняя граница равна Start, нижняя равна Exit,
	вывод данного подпункта меню осуществляет printMenu*/
	ParametersForMenu parametersForMenu = { Start, Exit, &printMenu };

	/*Пока пользователь не захочет выйти из этого подпункта меню,
	осуществляется перемещения по меню*/
	do
	{
		key = controlMenu(parametersForMenu);															// key получает значение пункта на котором остановился пользователь и нажал Enter

		/*После нажатия кнопки Enter, заходим в пункт который был выбран*/
		switch (key)
		{
		case Start:
			doPointStart(queue, flag);
			break;

		case Records:
			doPointRecords();
			break;

		default:
			break;
		}
	} while (key != Exit);
}