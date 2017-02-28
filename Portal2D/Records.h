#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include "Structures.h"
#include "List.h"

#define FILE_NAME_RECORDS "Records.txt"

namespace records           
{
	void overwriteFile(list::List *begin);
	int findingTheLocationInOrder(list::List *list, DataAboutTheChampion newChampion);
	void addInRecordsOrShowRecords(DataAboutTheChampion newChampion, char *variant);
	int knowFileSize(char *fileName);
	int countLettersInFile(char* variant, std::ifstream &fin);
	DataAboutTheChampion sortingDataAboutTheChampion(char *buf);
	void moveToNextLine(std::ifstream &fin);
	int countLengthLine(std::ifstream &finForSize);
}