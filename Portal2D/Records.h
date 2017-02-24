#pragma once

#include <string.h>
#include <iostream>
#include <fstream>
#include "Structures.h"

namespace records
{
	int knowFileSize(char *fileName);
	int countLettersInFile(char* fileName);
	void showAllOfRecords();
	DataAboutTheChampion sortingArrays(char *buf);
}