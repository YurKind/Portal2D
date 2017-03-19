#include "Search.h"

namespace search
{
	/* Выводит список на печать */
	void printFoundChampions(list::List<records::DataAboutTheChampion> *list)
	{
		if (!list)
		{
			std::cout << "\t\tNoone here, be the first!" << std::endl;
		}
		else
		{
			while (list)
			{
				std::cout << "\t\t\tname: " << list->value.name
					<< " level: " << list->value.level
					<< " score: " << list->value.score
					<< std::endl;

				list = list->next;
			}
		}
	}

	/* Поиск по очкам до первого результата */
	tree::BranchForNumber<records::DataAboutTheChampion> *searchByScoreOfOneResult(tree::BranchForNumber<records::DataAboutTheChampion> *tree, double score)
	{
		if (!tree || score == tree->data.score)     // если конец дерева или совпало кол-во очков
		{
			return tree;
		}

		if (score < tree->data.score)         // если параметр меньше чем кол-во очков текущего рекордсмена, то влево по дереву, иначе вправо
		{
			search::searchByScoreOfOneResult(tree->left, score);
		}
		else 
		{
			search::searchByScoreOfOneResult(tree->right, score);
		}
	}

	/* Поиск по уровню до первого результата */
	tree::BranchForNumber<records::DataAboutTheChampion> *searchByLevelOfOneResult(tree::BranchForNumber<records::DataAboutTheChampion> *tree, int level)
	{
		if (!tree || level == tree->data.level)     // если конец дерева или совпало кол-во очков
		{
			return tree;
		}

		if (level < tree->data.level)         // если параметр меньше чем уровень текущего рекордсмена, то влево по дереву, иначе вправо
		{
			search::searchByLevelOfOneResult(tree->left, level);
		}
		else
		{
			search::searchByLevelOfOneResult(tree->right, level);
		}
	}

	/* Поиск по имени до первого результата */
	tree::BranchForNumber<records::DataAboutTheChampion> *searchByStringOfOneResult(tree::BranchForNumber<records::DataAboutTheChampion> *tree, char *name)
	{
		if (!tree || comparison(name, tree->data.name) == 0)     // если конец дерева или совпало кол-во очков
		{
			return tree;
		}

		if (comparison(name, tree->data.name) < 0)         // если параметр меньше чем имя текущего рекордсмена, то влево по дереву, иначе вправо
		{
			search::searchByStringOfOneResult(tree->left, name);
		}
		else
		{
			search::searchByStringOfOneResult(tree->right, name);
		}
	}

	/* Сравнивает строки вне зависимости от регистра */
	int comparison(char *name, std::string str)
	{
		char *checking = new char[str.length() + 1];
		strcpy_s(checking, str.length() + 1, str.c_str());
		return _stricmp(name, checking);
	}
}
