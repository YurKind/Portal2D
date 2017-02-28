#include "Records.h"
#include "Structures.h"
#include "List.h"

void records::addInRecordsOrShowRecords(DataAboutTheChampion newChampion, char *variant)
{
	list::List *begin = NULL;
	begin = new list::List;
	std::ifstream fin(FILE_NAME_RECORDS);
	addList(&begin, fin);
	if (!strcmp(variant, "show"))
	{
		while (begin->next)
		{
			std::cout << "name: " << begin->champion.name << " level: " << begin->champion.level << " score: " << begin->champion.scores << std::endl;
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

void records::overwriteFile(list::List *begin)        // перезапись файла
{
	std::ofstream fout("Records.txt");
	while (begin->next != NULL)
	{
		fout << begin->champion.name << "|" << begin->champion.scores << "|" << begin->champion.level << ">";
		if (begin->next->next != NULL) {
			fout << std::endl;
		}
		begin = begin->next;
	}
	fout.close();
}

int records::findingTheLocationInOrder(list::List *begin, DataAboutTheChampion newChampion)      // высчитывание места нового рекордсмена в зависимости от уровня и очков
{
	int counter = 0;
	list::List *list = begin;
	while (list->champion.level > newChampion.level)
	{
		list = list->next;
		counter++;
	}
	while (list->champion.scores > newChampion.scores && list->champion.level == newChampion.level)
	{
		list = list->next;
		counter++;
	}

	return counter;
}

records::DataAboutTheChampion records::sortingDataAboutTheChampion(char *buf)
{
	char time[5], lvl[2];
	DataAboutTheChampion champion = {};
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
	int scores = atoi(time);
	champion.scores = scores;
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
