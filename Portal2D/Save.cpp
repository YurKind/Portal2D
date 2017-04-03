#include "Save.h"

void save::saveTheGame(game::GameInfo* gameInfo, game::MapCell** map)
{
	std::string slotName;

	system("cls");
	std::cout << "Enter the slot number: ";
	std::cin >> slotName;
	slotName = slotName + ".txt";

	std::ofstream fout(slotName);
}

void fillsOutDataFile(std::ofstream &fout)
{

}