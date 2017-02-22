#include "Menu.h"
#include "Structures.h"
#include "Records.h"

int menu::menu()
{
	cout << " press 1 to start a game\n press 2 to show ... \n";
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
	switch (playerChoice)
	{
	case START_GAME:
		//startGame(); TODO add this
		break;
	case INSTRUCTION:
		//showInstruction(); TODO add this
		break;
	case RECORDS:
		records::showTopOfRecords();
		break;
	case EXIT:
		break;
	default:
		cout << "You entered wrong key" << endl;
		system("cls");
		menu::functionCaller(menu::menu());
	}
}
