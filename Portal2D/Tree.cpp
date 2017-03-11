#include "Tree.h"
#include "Records.h"

namespace tree
{
	BranchForNumber<records::DataAboutTheChampion> *searchByScore(BranchForNumber<records::DataAboutTheChampion> *begin, double subjectOfSearch)
	{
		if (!begin || subjectOfSearch == begin->data.score)
		{
			return begin;
		}
		else if (subjectOfSearch < begin->data.score)
		{
			tree::searchByScore(begin->left, subjectOfSearch);
		}
		else
		{
			tree::searchByScore(begin->right, subjectOfSearch);
		}
	}

	void addTree(BranchForNumber<records::DataAboutTheChampion> **begin, char *fileName)
	{
		std::ifstream fin(FILE_NAME_RECORDS);
		tree::BranchForNumber<records::DataAboutTheChampion> *add = *begin;
		while (!fin.eof())
		{
			char *buf = new char[1024];
			fin.getline(buf, 1024);
			records::DataAboutTheChampion *data = new records::DataAboutTheChampion(records::initializationDataAboutTheChampion(buf));
			pushInTree(*data, add);
			delete data;
		}
		*begin = add;
	}

	void pushInTree(records::DataAboutTheChampion newData, BranchForNumber<records::DataAboutTheChampion> *&begin)
	{
		if (!begin)
		{
			begin = new tree::BranchForNumber<records::DataAboutTheChampion>;
			begin->data = newData;
		}
		else
		{
			if (begin->data.score > newData.score)
			{
				tree::pushInTree(newData, begin->left);
			}
			else
			{
				tree::pushInTree(newData, begin->right);
			}
		}
	}

	records::DataAboutTheChampion getMinimum(BranchForNumber<records::DataAboutTheChampion> *begin)
	{
		while (begin->left)
		{
			begin = begin->left;
		}
		return begin->data;
	}

	records::DataAboutTheChampion getMaximum(BranchForNumber<records::DataAboutTheChampion> *begin)
	{
		while (begin->right)
		{
			begin = begin->right;
		}
		return begin->data;
	}

	void freeMemory(BranchForNumber<records::DataAboutTheChampion> *begin)
	{
		if (begin)
		{
			tree::freeMemory(begin->left);
			tree::freeMemory(begin->right);
			delete begin;
		}
	}
}