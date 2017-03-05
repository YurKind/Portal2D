#pragma once
#include <string>
#include <iostream>
#include <fstream>

#define FILE_NAME_RECORDS "Records.txt"

namespace records
{
	struct DataAboutTheChampion
	{
		std::string name;
		int score;
		int level;
	};

	void overwriteFile(list::List<DataAboutTheChampion> *begin);

	int findingTheLocationInOrder(list::List<DataAboutTheChampion> *list, DataAboutTheChampion newChampion);

	void addInRecordsOrShowRecords(DataAboutTheChampion newChampion, char *variant);

	DataAboutTheChampion sortingDataAboutTheChampion(char *buf);

	void giveBestPlayerInLevel(int levelNumber);

	void removeItemsExcessLevels(list::List<DataAboutTheChampion> *begin, int rightLevel);

	int countLengthLine(std::ifstream &finForSize);
}