#pragma once

#include <string.h>
#include <iostream>
#include <fstream>
#include "Structures.h"

namespace records
{
	int findingTheLocationInOrder(List *list);
	void addInRecords();
	int knowFileSize(char *fileName);
	int countLettersInFile(char* variant, std::ifstream &fin);
	void showAllOfRecords();
	DataAboutTheChampion sortingArrays(char *buf, std::ifstream &fin, int number);
	void moveToNextLine(std::ifstream &fin);
	List* addList(DataAboutTheChampion champions[], int numberOfChampions);
}