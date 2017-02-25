#include "Records.h"
#include "Structures.h"
#include "List"

void records::freeMemory(List *begin)                 
{
	List *cleaner = begin;
	while (begin)              
	{
		cleaner = begin;         
		begin = begin->next;     
		delete cleaner;          
	}
}

void records::addInRecords(DataAboutTheChampion newChampion)
{
	List *begin = NULL;
	begin = new List;

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
		delete[] buf;
	}
	List *list = begin;
	records::addList(champions, N, begin);
	delete[] champions;
	int placeInRank = records::findingTheLocationInOrder(begin, N, newChampion);
	records::addInCertainPlace(begin, placeInRank, newChampion);
	overwriteFile(begin);
	finLine.close();
	finName.close();
	finAll.close();
	freeMemory(begin);
}

void records::overwriteFile(List *begin)
{
	std::ofstream fout("Records.txt");
	while (begin->next != NULL)
	{
		fout << begin->champion.name << "|" << begin->champion.scores << "|" << begin->champion.level << "|";
		if (begin->next->next != NULL) {
			fout << std::endl;
		}
		begin = begin->next;
	}
	fout.close();
}

void records::addList(DataAboutTheChampion champions[], int numberOfChampions, List *begin)
{
	List *add = begin;
	for (int i = 0; i < numberOfChampions; i++)
	{
		add->next = new List;
		add->champion = champions[i];
		add = add->next;
		add->next = NULL;
	}
}

int records::findingTheLocationInOrder(List *begin, int numberOfChampions, DataAboutTheChampion newChampion)
{
	int counter = 0;
	List *list = begin;
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

void records::addInCertainPlace(List *begin, int placeNumber, DataAboutTheChampion newChampion)
{
	List *insert = begin;
	for (int i = 0; i < placeNumber - 1; i++)
	{
		insert = insert->next;
	}
	List *end = insert->next;
	List *add = new List;
	insert->next = add;
	add->champion = newChampion;
	add->next = end;
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
	fin.close();
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

DataAboutTheChampion records::sortingArrays(char *buf, std::ifstream &fin, int callNumber)
{
	char time[5], lvl[2];
	DataAboutTheChampion champion;
	int counterLetter = 0, i = 0, fileSize = knowFileSize("Records.txt");
	int sizeName = records::countLettersInFile("name", fin);
	char *name = new char[sizeName];

	while (buf[counterLetter] != '|')
	{
		name[counterLetter] = buf[counterLetter];
		counterLetter++;
	}
	counterLetter++;

	static std::string *str;
	if (callNumber == 0)
	{
		str = new std::string[fileSize];
	} 
	
	for (int j = 0; j < sizeName - 2; j++)
	{
		str[callNumber] += name[j];
	}
	champion.name = &str[callNumber][0];
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

	if (callNumber == fileSize)
	{
		delete[] str;
	}

	return champion;
}
