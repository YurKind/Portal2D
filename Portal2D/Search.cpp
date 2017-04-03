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
		if (!tree || score <= tree->data.score)     // если конец дерева или совпало кол-во очков
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

	/* Поиск по подстроке в строке */
	records::DataAboutTheChampion searchBySubstringOfOneResult(records::DataAboutTheChampion subjectOfSearch, char *substring)
	{
		bool flag = false;
		int lengthOfSubstring = 0;
		records::DataAboutTheChampion result = subjectOfSearch; 
		char *stringForSearch = new char[subjectOfSearch.name.length() + 1];     
		strcpy_s(stringForSearch, subjectOfSearch.name.length() + 1, subjectOfSearch.name.c_str());

		for (lengthOfSubstring = 0; substring[lengthOfSubstring]; lengthOfSubstring++);      // вычисление размера подстроки

		if (subjectOfSearch.name.length() < lengthOfSubstring) 
		{
			result.level = -1;      // результат поиска отрицательный
		}
		else
		{
			for (int i = 0, j = 0; i <= subjectOfSearch.name.length() && j <= lengthOfSubstring && !flag; i++, j++)
			{
				if (j == lengthOfSubstring)
					flag = true;         // результат поиска положительный

				if (!(stringForSearch[i] == substring[j]))
					j = -1;			
			}
		}

		if (!flag)
			result.level = -1;

		delete[] stringForSearch;
		return result;
	}

	/* Поиск по подстроке всех элементов из файла мс рекордами */
	list::List<records::DataAboutTheChampion> *searchBySubstringAllResults(list::List<records::DataAboutTheChampion> *result, char *substring)
	{
		list::List<records::DataAboutTheChampion> *list = new list::List<records::DataAboutTheChampion>;
		std::ifstream fin(FILE_NAME_RECORDS);
		records::DataAboutTheChampion temp;
		list::addList(&list, fin);

		while (list)
		{
			temp = searchBySubstringOfOneResult(list->value, substring);

			if (temp.level != -1)
			{
				list::addBegin(&result, temp);
			}
			list = list->next;
		}

		list::freeMemory(list);
		return result;
	}
}
