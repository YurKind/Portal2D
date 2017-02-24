#include "Records.h"
#include "Structures.h"


void records::addRecords() 
{
	std::ifstream fin("Records.txt");
	std::ofstream fout("Records.txt");
	int counterInit = records::countLettersInFile("Records.txt", "line", fin);
	int N = records::knowFileSize("Records.txt");
	DataAboutTheChampion *champions = new DataAboutTheChampion[N];

	for (int i = 0; i < N; i++)
	{
		char *buf = new char[counterInit];
		fin.getline(buf, counterInit);
		champions[i] = records::sortingArrays(buf, fin);
		delete[] buf;
	}
}

void records::showAllOfRecords()
{
	std::ifstream finLine("Records.txt");
	std::ifstream finName("Records.txt");
	std::ifstream finAll("Records.txt");
	int N = records::knowFileSize("Records.txt");

	for (int i = 0; i < N; i++)
	{
		int counterInit = records::countLettersInFile("Records.txt", "line", finLine);
		char *buf = new char[counterInit];
		finAll.getline(buf, counterInit);
		DataAboutTheChampion champion = records::sortingArrays(buf, finName);
		std::cout << "\nname: " << champion.name << " scores: " << champion.scores << " lvl: " << champion.level << "";
		delete[] buf;
	}
	finAll.close();
}

int findingTheLocationInOrder() 
{
	return 0;
}

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

int records::countLettersInFile(char* fileName, char* variant, std::ifstream &fin)
{
	char temp = NULL;
	char* buf = new char[1000];
	int counter = 0;
	if (!strcmp(variant, "name"))
	{
		while (!fin.eof())
		{
			if (temp == '|')
				break;
			fin >> temp;
			counter++;
		}
	}
	else if (!strcmp(variant, "line"))
	{
		char temp = NULL;
		fin.getline(buf, 1000);
		while (buf[counter] != '\0')
		{
			buf[counter++] >> temp;
		}
	}
	delete[] buf;
	return counter;
}

DataAboutTheChampion records::sortingArrays(char *buf, std::ifstream &fin)
{
	char time[5], lvl[2];
	DataAboutTheChampion champion;
	int counterLetter = 0, i = 0, size = 0;
	int sizeName = records::countLettersInFile("Records.txt", "name", fin);
	char *name = new char[sizeName];

	while (buf[counterLetter] != '|')
	{
		name[counterLetter] = buf[counterLetter];
		counterLetter++;
	}
	counterLetter++;

	static std::string str = "";
	for (int j = 0; j < sizeName - 1; j++)
	{
		str += name[j];
	}
	champion.name = &str[0];

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

	while (buf[counterLetter] != '|')
	{
		lvl[i] = buf[counterLetter];
		counterLetter++;
		i++;
	}
	int level = atoi(lvl);
	champion.level = level;

	return champion;
}

