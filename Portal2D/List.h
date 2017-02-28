#pragma once

#include "Records.h"

namespace list
{
	void addList(List **begin, std::ifstream &fin);
	void freeMemory(List *begin);
	void addBegin(List **begin, records::DataAboutTheChampion newChampion);
	void addInCertainPlace(List **begin, int placeNumber, records::DataAboutTheChampion newChampion);
}