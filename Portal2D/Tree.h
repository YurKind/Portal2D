#pragma once
#include "Structures.h"

namespace tree
{
	list::List<records::DataAboutTheChampion> *searchByScoreAllElements(BranchForNumber<records::DataAboutTheChampion> *begin, double score);

	BranchForNumber<records::DataAboutTheChampion> *searchByScoreOfOneResult(BranchForNumber<records::DataAboutTheChampion> *begin, double subjectOfSearch);

	void pushInTree(records::DataAboutTheChampion newData, BranchForNumber<records::DataAboutTheChampion> *&begin);

	records::DataAboutTheChampion getMinimum(BranchForNumber<records::DataAboutTheChampion> *begin);

	records::DataAboutTheChampion getMaximum(BranchForNumber<records::DataAboutTheChampion> *begin);

	void freeMemory(tree::BranchForNumber<records::DataAboutTheChampion> *begin);

	void addTree(tree::BranchForNumber<records::DataAboutTheChampion> **begin, char *fileName);
}