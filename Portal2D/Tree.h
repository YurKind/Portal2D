#pragma once
#include "Structures.h"

enum Parametr
{
	SCORE = 1, LEVEL = 2, STRING = 3
};

namespace tree
{
	void pushInTree(records::DataAboutTheChampion newData, BranchForNumber<records::DataAboutTheChampion> *&begin, int variant);

	records::DataAboutTheChampion getMinimum(BranchForNumber<records::DataAboutTheChampion> *begin);

	records::DataAboutTheChampion getMaximum(BranchForNumber<records::DataAboutTheChampion> *begin);

	void freeMemory(tree::BranchForNumber<records::DataAboutTheChampion> *begin);

	void addTree(BranchForNumber<records::DataAboutTheChampion> **begin, char *fileName, int variant);
}