#include "Records.h"
#include "Structures.h"
#include "List"

void records::addInRecords() 
{
	std::ifstream fin("Records.txt");
	std::ofstream fout("Records.txt");
	int counterInit = records::countLettersInFile("line", fin);
	int N = records::knowFileSize("Records.txt");
	DataAboutTheChampion *champions = new DataAboutTheChampion[N];

	for (int i = 0; i < N; i++)
	{
		char *buf = new char[counterInit];
		fin.getline(buf, counterInit);
		champions[i] = records::sortingArrays(buf, fin, i);
		delete[] buf;
	}
	List *list = records::addList(champions, N);

}

int records::findingTheLocationInOrder(List *list)
{
	return 0;
}

List* records::addList(DataAboutTheChampion champions[], int numberOfChampions)
{
	List *begin = NULL;
	begin = new List;
	
	for (int i = 0; i < numberOfChampions; i++)
	{
		begin->next = new List;
		begin->champion = champions[i];
		begin = begin->next;
		begin->next = NULL;
	}

	return begin;
}

void records::showAllOfRecords()
{
	std::ifstream finLine("Records.txt"), finName("Records.txt"), finAll("Records.txt");
	int N = records::knowFileSize("Records.txt");
	DataAboutTheChampion *champions = new DataAboutTheChampion[N];

	for (int i = 0; i < N; i++)
	{
		int counterInit = records::countLettersInFile("line", finLine);
		char *buf = new char[counterInit];
		finAll.getline(buf, counterInit);
		champions[i] = records::sortingArrays(buf, finName, i);
		moveToNextLine(finName);
		std::cout << "\nname: " << champions[i].name << " scores: " << champions[i].scores << " lvl: " << champions[i].level << "";
		delete[] buf;
	}
	delete[] champions;
	finAll.close();
	finLine.close();
	finName.close();
}

void records::moveToNextLine(std::ifstream &fin)
{
	char *b = new char[20];
	fin.getline(b, 20);
	delete[] b;
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

int records::countLettersInFile(char* variant, std::ifstream &fin)
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
		while (buf[counter] != '\0') {
			counter++;
		}
	}
	delete[] buf;
	return ++counter;
}

DataAboutTheChampion records::sortingArrays(char *buf, std::ifstream &fin, int number)
{
	char time[5], lvl[2];
	DataAboutTheChampion champion;
	int counterLetter = 0, i = 0, size = 0;
	int sizeName = records::countLettersInFile("name", fin);
	char *name = new char[sizeName];

	while (buf[counterLetter] != '|')
	{
		name[counterLetter] = buf[counterLetter];
		counterLetter++;
	}
	counterLetter++;

	static std::string *str = new std::string[knowFileSize("Records.txt")];
	for (int j = 0; j < sizeName - 2; j++)
	{
		str[number] += name[j];
	}
	champion.name = &str[number][0];
	delete[] name;

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

