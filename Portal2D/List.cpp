#include "List.h"

void list::addList(List **begin, std::ifstream &fin)          // создание и инициализация списка
{
	List *add = *begin;
	std::ifstream finForSize(FILE_NAME_RECORDS);
	char *buf = NULL;
	while (!fin.eof())
	{
		int lengthLine = records::countLengthLine(finForSize);
		buf = new char[lengthLine];
		fin.getline(buf, lengthLine);
		add->next = new List;
		add->champion = records::sortingDataAboutTheChampion(buf);
		add = add->next;
		add->next = NULL;
	}
	finForSize.close();
	delete[] buf;
}

void list::addBegin(List **begin, records::DataAboutTheChampion newChampion)        // вставка в начало списка
{
	List *add = new List;
	add->champion = newChampion;
	add->next = *begin;
	*begin = add;
}

void list::addInCertainPlace(List **begin, int placeNumber, records::DataAboutTheChampion newChampion)       // вставка элемента списка с новым рекордсменом на соответствующее место 
{
	if (placeNumber == 0)
	{
		addBegin(begin, newChampion);           // всавка в начало списка
	}
	else
	{
		List *insert = *begin;         // новый указатель на начало списка
		for (int i = 0; i < placeNumber - 1; i++)
		{
			insert = insert->next;      // передвигаемся до нужного места
		}
		List *end = insert->next;       // указатель на элемент на который будет ссылаться новый элемент списка 
		List *add = new List;           // новый элемент
		insert->next = add;             // указатель предыдущего элемента на новый элемент
		add->champion = newChampion;    // инициализация нового элемента
		add->next = end;                // указатель нового элемента к следующему элементу списка
	}
}

void list::freeMemory(List *begin)       // освобождение памяти от списка 
{
	List *cleaner = begin;        // новый указатель на начало списка
	while (begin)
	{
		cleaner = begin;
		begin = begin->next;
		delete cleaner;
	}
}