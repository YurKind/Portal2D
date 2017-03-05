#include "Menu.h"
#include "Records.h"
#include "Gameplay.h"

int menu::menu()
{
	cout << " press 1 to start a game\n press 2 to show instuction \n press 3 to show high scores \n press 4 to exit";
	switch (_getch())
	{
	case StartGame:
		return StartGame;

	case Instruction:
		return Instruction;

	case HighScores:
		return HighScores;

	case Exit:
		return Exit;

	default:
		return NULL;
	}
}

void menu::functionCaller(int playerChoice)
{
<<<<<<< HEAD
<<<<<<< HEAD
	DataAboutTheChampion newChampion = { "000000", 55, 8 };
	switch (playerChoice)
=======
<<<<<<< HEAD
	switch (a)
=======
	records::DataAboutTheChampion newChampion = { "-1-1-1-1-1-1-1", 1000, 10 };
	switch (playerChoice)
>>>>>>> Andrey
>>>>>>> 3961de4c8b60b1c3db86816a25f7d5b5ac4d20df
=======
	switch (a)
>>>>>>> c09189a9eefbd98c72a8542b92ffdd1a625975fd
	{
	case StartGame:
		// TODO: Rework!
		game::levelOne();
		break;
<<<<<<< HEAD
<<<<<<< HEAD
	case Instruction:
		cout << "In development" << endl;
		//showInstruction(); TODO add this    
=======
<<<<<<< HEAD
=======
>>>>>>> c09189a9eefbd98c72a8542b92ffdd1a625975fd
	case 3:cout << "Level 2";
		break;
	case 4:cout << "Level 3";
		break;
	case 5:cout << "Level 4";
		break;
	case 6:cout << "Level 5";
		break;
	case 7:
		Point();

		MoveToMenuPoint();
		break;
	}
}
void UserSelection3(int Cur)
{
	system("cls");
	switch (Cur)
	{
	case 1: cout << "All Records";
>>>>>>> 3961de4c8b60b1c3db86816a25f7d5b5ac4d20df
		break;
	case HighScores:
		records::showAllOfRecords();
		records::addInRecords(newChampion);
		break;
	case Exit:
		exit(0);
		break;
<<<<<<< HEAD
<<<<<<< HEAD
=======
=======

	case INSTRUCTION:
		cout << "In development" << endl;
		//showInstruction(); TODO add this    
		break;

	case RECORDS:
		system("cls");
		records::addInRecordsOrShowRecords(newChampion, "show");
		records::addInRecordsOrShowRecords(newChampion, "add");
		records::addInRecordsOrShowRecords(newChampion, "show");
		records::giveBestPlayerInLevel(10);
		break;

	case EXIT:
		break;

>>>>>>> 3961de4c8b60b1c3db86816a25f7d5b5ac4d20df
	default:
		cout << "You entered wrong key" << endl;
		system("cls");
		menu::functionCaller(menu::menu());
<<<<<<< HEAD
=======
>>>>>>> Andrey
>>>>>>> 3961de4c8b60b1c3db86816a25f7d5b5ac4d20df
=======
>>>>>>> c09189a9eefbd98c72a8542b92ffdd1a625975fd
	}
}
