#include "Records.h"
#include "Structures.h"

void records::showTopOfRecords()
{
	int counterInit = records::countLettersInFile("Records.txt");
	char *buf = new char[counterInit];
	buf = records::initBuffer("Records.txt", counterInit);
	DataAboutTheChampion champion = records::sortingArrays(buf);
	std::cout << "name: " << champion.name << " scores: " << champion.scores << " lvl: " << champion.level;
}

char* records::initBuffer(char* fileName, int size)
{
	std::ifstream fin(fileName);
	char *buf = new char[size];
	fin.getline(buf, size);
	fin.close();
	return buf;
}

int records::countLettersInFile(char* fileName)
{
	int counter = 0;
	std::ifstream fin(fileName);
	while (!fin.eof())
	{
		char c;
		fin >> c;
		counter++;
	}
	fin.close();
	return counter;
}

DataAboutTheChampion records::sortingArrays(char *buf)
{
	char time[5], lvl[5];
	DataAboutTheChampion champion;
	int counterLetter = 0, i = 0, size = 0;
	char *name = new char[20];

	while (buf[counterLetter] != '|')
	{
		name[counterLetter] = buf[counterLetter];
		counterLetter++;
	}
	counterLetter++;
	champion.name = name;

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

	while (buf[counterLetter] != '\0')
	{
		lvl[i] = buf[counterLetter];
		counterLetter++;
		i++;
	}
	int level = atoi(lvl);
	champion.level = level;

	return champion;
}

