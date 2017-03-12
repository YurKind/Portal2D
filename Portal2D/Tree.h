#pragma once
#include "Structures.h"

enum Parametr {
	SCORE = 1, LEVEL = 2, STRING = 3
};

namespace tree
{
	void setSearchParametr(int parametr);

	void printFoundChampions(list::List<records::DataAboutTheChampion> *list);

	list::List<records::DataAboutTheChampion> *searchByLevelAllElements(BranchForNumber<records::DataAboutTheChampion> *begin, int level);

	BranchForNumber<records::DataAboutTheChampion> *searchByLevelOfOneResult(BranchForNumber<records::DataAboutTheChampion> *begin, int level);

	list::List<records::DataAboutTheChampion> *searchByScoreAllElements(BranchForNumber<records::DataAboutTheChampion> *begin, double score);

	BranchForNumber<records::DataAboutTheChampion> *searchByScoreOfOneResult(BranchForNumber<records::DataAboutTheChampion> *begin, double subjectOfSearch);

	void pushInTreeByLevel(records::DataAboutTheChampion newData, BranchForNumber<records::DataAboutTheChampion> *&begin);

	void pushInTreeByScore(records::DataAboutTheChampion newData, BranchForNumber<records::DataAboutTheChampion> *&begin);

	records::DataAboutTheChampion getMinimum(BranchForNumber<records::DataAboutTheChampion> *begin);

	records::DataAboutTheChampion getMaximum(BranchForNumber<records::DataAboutTheChampion> *begin);

	void freeMemory(tree::BranchForNumber<records::DataAboutTheChampion> *begin);

	void addTree(BranchForNumber<records::DataAboutTheChampion> **begin, char *fileName, int variant);
}