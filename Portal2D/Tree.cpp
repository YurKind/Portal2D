#include "Tree.h"
#include "Records.h"
#include "List.h"
#include <conio.h>

namespace tree
{
	void addTree(BranchForNumber<records::DataAboutTheChampion> **begin, char *fileName, int variant)
	{
		std::ifstream fin(FILE_NAME_RECORDS);
		tree::BranchForNumber<records::DataAboutTheChampion> *add = *begin;
		while (!fin.eof())
		{
			char *buf = new char[1024];
			fin.getline(buf, 1024);
			records::DataAboutTheChampion *data = new records::DataAboutTheChampion(records::initializationDataAboutTheChampion(buf));
			if (variant == SCORE)
			{
				pushInTree(*data, add, SCORE);
			}
			else if (variant == LEVEL)
			{
				pushInTree(*data, add, LEVEL);
			}
			else if (variant == STRING)
			{
				
			}
			else if (variant == STRING)
			{

			}
			delete data;
			delete[] buf;
		}
		*begin = add;
		fin.close();
	}

	void pushInTree(records::DataAboutTheChampion newData, BranchForNumber<records::DataAboutTheChampion> *&begin, int variant)
	{
		if (!begin)
		{
			begin = new tree::BranchForNumber<records::DataAboutTheChampion>;
			begin->data = newData;
		}
		else 
		{
			if (variant == SCORE)
			{
				if (begin->data.score > newData.score)
				{
					tree::pushInTree(newData, begin->left, SCORE);
				}
				else
				{
					tree::pushInTree(newData, begin->right, SCORE);
				}
			}
			else if (variant == LEVEL)
			{
				if (begin->data.level > newData.level)
				{
					tree::pushInTree(newData, begin->left, LEVEL);
				}
				else
				{
					tree::pushInTree(newData, begin->right, LEVEL);
				}
			}
			else if (variant == STRING)
			{
				
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
/*void pushInTreeByScore(records::DataAboutTheChampion newData, BranchForNumber<records::DataAboutTheChampion> *&begin)
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
				tree::pushInTreeByScore(newData, begin->left);
			}
			else
			{
				tree::pushInTreeByScore(newData, begin->right);
			}
		}
	}

	void pushInTreeByLevel(records::DataAboutTheChampion newData, BranchForNumber<records::DataAboutTheChampion> *&begin)
	{
		if (!begin)
		{
			begin = new tree::BranchForNumber<records::DataAboutTheChampion>;
			begin->data = newData;
		}
		else
		{
			if (begin->data.level > newData.level)
			{
				tree::pushInTreeByLevel(newData, begin->left);
			}
			else
			{
				tree::pushInTreeByLevel(newData, begin->right);
			}
		}
	}*/