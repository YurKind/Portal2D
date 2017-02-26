#include "Menu.h"
#include "Structures.h"
#include "Records.h"
#include "Gameplay.h"

int menu::menu()
{
	cout << " press 1 to start a game\n press 2 to show instuction \n press 3 to show high scores \n press 4 to exit";
	switch (_getch())
	{
	case START_GAME:
		return START_GAME;

	case INSTRUCTION:
		return INSTRUCTION;

	case RECORDS:
		return RECORDS;

	case EXIT:
		return EXIT;

	default:
		return NULL;
	}
}

void menu::functionCaller(int playerChoice)
{
	DataAboutTheChampion newChampion = { "-1-1-1-1-1-1-1", 47, 10 };
	switch (playerChoice)
	{
	case START_GAME:
		// TODO: Rework!
		game::levelOne();
		break;
	case INSTRUCTION:
		cout << "In development" << endl;
		//showInstruction(); TODO add this    
		break;
	case RECORDS:
		records::showAllOfRecords();
		records::addInRecords(newChampion);
		break;
	case EXIT:
		break;
	default:
		cout << "You entered wrong key" << endl;
		system("cls");
		menu::functionCaller(menu::menu());
	}
}
