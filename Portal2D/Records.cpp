#include "Records.h"
#include "Structures.h"
#include "List.h"
#include "SortingMethods.h"

void records::addInRecordsOrShowRecords(records::DataAboutTheChampion newChampion, char *variant)
{
	list::List<records::DataAboutTheChampion> *begin = new list::List<records::DataAboutTheChampion>;
	std::ifstream fin(FILE_NAME_RECORDS);
	addList(&begin, fin);
	if (!strcmp(variant, "show"))
	{
		while (begin->next)
		{
			std::cout << "name: " << begin->value.name << " level: " << begin->value.level << " score: " << begin->value.score << std::endl;
			begin = begin->next;
		}
	}
	else if (!strcmp(variant, "add"))
	{
		int placeInRank = records::findingTheLocationInOrder(begin, newChampion);
		list::addInCertainPlace(&begin, placeInRank, newChampion);
		records::overwriteFile(begin);
	}
	fin.close();
	list::freeMemory(begin);
}

void records::giveBestPlayerInLevel(int levelNumber)
{
	list::List<records::DataAboutTheChampion> *begin = new list::List<records::DataAboutTheChampion>;;
	begin->next = NULL;
	std::ifstream fin(FILE_NAME_RECORDS);
	addList(&begin, fin);
	records::removeItemsExcessLevels(begin, levelNumber);
	std::cout << " -> name: " << begin->value.name << " level: " << begin->value.level << " score: " << begin->value.score << std::endl;
	fin.close();
	list::freeMemory(begin);
}

void records::removeItemsExcessLevels(list::List<records::DataAboutTheChampion> *begin, int rightLevel)
{
	list::List<records::DataAboutTheChampion> *cleaner = begin;        // новый указатель на начало списка
	list::List<records::DataAboutTheChampion> *end = NULL;
	while (begin)
	{
		if (begin->value.level != rightLevel)
		{
			end->next = NULL;
			cleaner = begin;
			begin = begin->next;
			delete cleaner;
		}
		else
		{
			end = begin;
			begin = begin->next;
		}
	}
}

int records::countLengthLine(std::ifstream &finForSize)
{
	int lengthLine = 0;
	char temp = ' ';
	while (temp != '>')
	{
		finForSize >> temp;
		lengthLine++;
	}
	return ++lengthLine;
}

void records::overwriteFile(list::List<records::DataAboutTheChampion> *begin)        // перезапись файла
{
	std::ofstream fout("Records.txt");
	while (begin->next != NULL)
	{
		fout << begin->value.name << "|" << begin->value.score << "|" << begin->value.level << ">";
		if (begin->next->next != NULL) {
			fout << std::endl;
		}
		begin = begin->next;
	}
	fout.close();
}

int records::findingTheLocationInOrder(list::List<records::DataAboutTheChampion> *begin, records::DataAboutTheChampion newChampion)      // высчитывание места нового рекордсмена в зависимости от уровня и очков
{
	int counter = 0;
	list::List<records::DataAboutTheChampion> *list = begin;
	while (list->value.level > newChampion.level)
	{
		list = list->next;
		counter++;
	}
	while (list->value.score > newChampion.score && list->value.level == newChampion.level)
	{
		list = list->next;
		counter++;
	}

	return counter;
}

records::DataAboutTheChampion records::sortingDataAboutTheChampion(char *buf)
{
	char time[5], lvl[2];
	records::DataAboutTheChampion champion = {};
	int counterLetter = 0, i = 0;
	while (buf[counterLetter] != '|')
	{
		champion.name += buf[counterLetter];
		counterLetter++;
	}
	counterLetter++;
	while (buf[counterLetter] != '|')
	{
		time[i] = buf[counterLetter];
		counterLetter++;
		i++;
	}
	int score = atoi(time);
	champion.score = score;
	counterLetter++;
	i = 0;
	while (buf[counterLetter] != '>')
	{
		lvl[i] = buf[counterLetter];
		counterLetter++;
		i++;
	}
	int level = atoi(lvl);
	champion.level = level;

	return champion;
}
