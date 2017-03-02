#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include "Structures.h"
#include "List.h"

#define FILE_NAME_RECORDS "Records.txt"

namespace records
{
	void overwriteFile(list::List<records::DataAboutTheChampion> *begin);

	int findingTheLocationInOrder(list::List<records::DataAboutTheChampion> *list, records::DataAboutTheChampion newChampion);


	void addInRecordsOrShowRecords(records::DataAboutTheChampion newChampion, char *variant);

	records::DataAboutTheChampion sortingDataAboutTheChampion(char *buf);

	int countLengthLine(std::ifstream &finForSize);
}