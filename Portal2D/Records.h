#pragma once

#include <string.h>
#include <iostream>
#include <fstream>
#include "Structures.h"

namespace records
{
	void addRecords();
	int knowFileSize(char *fileName);
	int countLettersInFile(char* variant, std::ifstream &fin);
	void showAllOfRecords();
	DataAboutTheChampion sortingArrays(char *buf, std::ifstream &fin, int number);
	void clean(std::ifstream &fin);
}