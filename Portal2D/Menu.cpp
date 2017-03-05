#include "Menu.h"
#include "Structures.h"
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
	DataAboutTheChampion newChampion = { "000000", 55, 8 };
	switch (playerChoice)
	{
	case StartGame:
		// TODO: Rework!
		game::levelOne();
		break;
	case Instruction:
		cout << "In development" << endl;
		//showInstruction(); TODO add this    
		break;
	case HighScores:
		records::showAllOfRecords();
		records::addInRecords(newChampion);
		break;
	case Exit:
		exit(0);
		break;
	default:
		cout << "You entered wrong key" << endl;
		system("cls");
		menu::functionCaller(menu::menu());
	}
}
