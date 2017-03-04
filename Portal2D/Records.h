#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "List.h"

#define FILE_NAME_RECORDS "Records.txt"

namespace records
{
	struct DataAboutTheChampion
	{
		std::string name;
		int score;
		int level;
	};

	void overwriteFile(list::List<records::DataAboutTheChampion> *begin);

	int findingTheLocationInOrder(list::List<records::DataAboutTheChampion> *list, records::DataAboutTheChampion newChampion);

	void addInRecordsOrShowRecords(records::DataAboutTheChampion newChampion, char *variant);

	records::DataAboutTheChampion sortingDataAboutTheChampion(char *buf);

	void giveBestPlayerInLevel(int levelNumber);

	void removeItemsExcessLevels(list::List<records::DataAboutTheChampion> *begin, int rightLevel);

	int countLengthLine(std::ifstream &finForSize);
}