#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "Structures.h"

#define FILE_NAME_RECORDS "Records.txt"

namespace records
{
	void overwriteFile(list::List<DataAboutTheChampion> *begin);

	int findingTheLocationInOrder(list::List<DataAboutTheChampion> *list, DataAboutTheChampion newChampion);

	void addInRecordsOrShowRecords(DataAboutTheChampion newChampion, char *variant);

	DataAboutTheChampion sortingDataAboutTheChampion(char *buf);

	void giveBestPlayerInLevel(int levelNumber);

	void removeItemsExcessLevels(list::List<DataAboutTheChampion> *begin, int rightLevel);

	int countLengthLine(std::ifstream &finForSize);
}