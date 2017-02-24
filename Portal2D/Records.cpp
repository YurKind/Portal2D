#include "Records.h"
#include "Structures.h"

int records::knowFileSize(char *fileName)
{
	int count = 0;
	std::ifstream fin(fileName);
	while (!fin.eof()) 
	{
		char *arr = new char[1024];
		fin.getline(arr, 1024);
		count++;
		delete[] arr;
	}
	return count;
}

void records::showAllOfRecords()
{
	std::ifstream fin("Records.txt");
	int N = records::knowFileSize("Records.txt");
	DataAboutTheChampion *champions = new DataAboutTheChampion[N];
	int counterInit = records::countLettersInFile("Records.txt");
	for (int i = 0; i < N; i++)
	{
		char *buf = new char[counterInit];
		fin.getline(buf, counterInit);
		DataAboutTheChampion champion = records::sortingArrays(buf);
		std::cout << "\nname: " << champion.name << " scores: " << champion.scores << " lvl: " << champion.level << "";
	}
	fin.close();
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

