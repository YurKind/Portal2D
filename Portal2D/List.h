
#pragma once
#include "Records.h"

namespace list
{
	void addList(List<records::DataAboutTheChampion> **begin, std::ifstream &fin);

	void freeMemory(List<records::DataAboutTheChampion> *begin);

	template<class T1, class T2>
	void addBegin(T1 **begin, T2 newChampion);

	void addInCertainPlace(List<records::DataAboutTheChampion> **begin, int placeNumber, records::DataAboutTheChampion newChampion);
}
