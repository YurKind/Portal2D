#pragma once

#include <string.h>
#include <iostream>
#include <fstream>
#include "Structures.h"

namespace records
{
	void overwriteFile(List *begin);
	void addInCertainPlace(List *begin, int placeNumber, DataAboutTheChampion newChampion);
	void freeMemory(List *begin);
	int findingTheLocationInOrder(List *list, int numberOfChampions, DataAboutTheChampion newChampion);
	void addInRecords(DataAboutTheChampion newChampion);
	int knowFileSize(char *fileName);
	int countLettersInFile(char* variant, std::ifstream &fin);
	void showAllOfRecords();
	DataAboutTheChampion sortingArrays(char *buf, std::ifstream &fin, int callNumber);
	void moveToNextLine(std::ifstream &fin);
	void addList(DataAboutTheChampion champions[], int numberOfChampions, List *begin);
}