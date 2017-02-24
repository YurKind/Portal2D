#pragma once

#include <string.h>
#include <iostream>
#include <fstream>
#include "Structures.h"

namespace records
{
	void Free_memory(List *begin);
	int findingTheLocationInOrder(List *list, int numberOfChampions, DataAboutTheChampion newChampion);
	void addInRecords(DataAboutTheChampion newChampion);
	int knowFileSize(char *fileName);
	int countLettersInFile(char* variant, std::ifstream &fin);
	void showAllOfRecords();
	DataAboutTheChampion sortingArrays(char *buf, std::ifstream &fin, int number);
	void moveToNextLine(std::ifstream &fin);
	List* addList(DataAboutTheChampion champions[], int numberOfChampions, List *begin);
}