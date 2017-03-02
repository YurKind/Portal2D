#include "Records.h"
#include "Structures.h"
#include "List.h"

void records::addInRecordsOrShowRecords(records::DataAboutTheChampion newChampion, char *variant)
{
	list::List<records::DataAboutTheChampion> *begin = new list::List<records::DataAboutTheChampion>;
	std::ifstream fin(FILE_NAME_RECORDS);
	addList(&begin, fin);
	if (!strcmp(variant, "show"))
	{
		while (begin->next)
		{
			std::cout << "name: " << begin->value.name << " level: " << begin->value.level << " score: " << begin->value.scores << std::endl;
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

void records::overwriteFile(list::List<records::DataAboutTheChampion> *begin)        // перезапись файла
{
	std::ofstream fout("Records.txt");
	while (begin->next != NULL)
	{
		fout << begin->value.name << "|" << begin->value.scores << "|" << begin->value.level << ">";
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
	while (list->value.scores > newChampion.scores && list->value.level == newChampion.level)
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
