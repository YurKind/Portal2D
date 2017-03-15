#pragma once
#include "Tree.h"
#include "Records.h"
#include "List.h"
#include <conio.h>

namespace search
{
	void setSearchParametr(int parametr);

	void printFoundChampions(list::List<records::DataAboutTheChampion> *list);

	list::List<records::DataAboutTheChampion> *searchByLevelAllElements(tree::BranchForNumber<records::DataAboutTheChampion> *begin, int level);

	tree::BranchForNumber<records::DataAboutTheChampion> *searchByLevelOfOneResult(tree::BranchForNumber<records::DataAboutTheChampion> *begin, int level);

	list::List<records::DataAboutTheChampion> *searchByScoreAllElements(tree::BranchForNumber<records::DataAboutTheChampion> *begin, double score);

	tree::BranchForNumber<records::DataAboutTheChampion> *searchByScoreOfOneResult(tree::BranchForNumber<records::DataAboutTheChampion> *begin, double subjectOfSearch);
}