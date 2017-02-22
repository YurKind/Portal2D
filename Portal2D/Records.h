#pragma once

#include <iostream>
#include <fstream>
#include "Structures.h"

namespace records
{
	int countLettersInFile(char* fileName, char* x);
	char* initBuffer(char* fileName, int number);
	void showTopOfRecords();
	DataAboutTheChampion sortingArrays(char *buf);
}