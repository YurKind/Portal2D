#include "List.h"
#include "Definitions.h"

void list::addList(list::List<records::DataAboutTheChampion> **list, std::ifstream &fin)          // создание и инициализаци€ списка
{
	list::List<records::DataAboutTheChampion> *add = *list;
	std::ifstream finForSize(FILE_NAME_RECORDS);
	char *buf = NULL;

	while (!fin.eof())
	{
		int lengthLine = records::countLengthLine(finForSize);     // узнаем длинну строки дл€ объ€влени€ массива-буфера
		buf = new char[lengthLine];
		fin.getline(buf, lengthLine);
		add->next = new list::List<records::DataAboutTheChampion>;
		add->value = records::initializationDataAboutTheChampion(buf);
		add = add->next;
		add->next = NULL;
		delete[] buf;
	}
	finForSize.close();
}

void list::addInCertainPlace(list::List<records::DataAboutTheChampion> **begin, int placeNumber, records::DataAboutTheChampion newChampion)       // вставка элемента списка с новым рекордсменом на соответствующее место 
{
	if (placeNumber == 0)
	{
		list::addBegin(begin, newChampion);           // вставка в начало списка
	}
	else
	{
		list::List<records::DataAboutTheChampion> *insert = *begin;         // новый указатель на начало списка

		for (int i = 0; i < placeNumber - 1; i++)
		{
			insert = insert->next;      // передвигаемс€ до нужного места
		}
		list::List<records::DataAboutTheChampion> *end = insert->next;       // указатель на элемент на который будет ссылатьс€ новый элемент списка 
		list::List<records::DataAboutTheChampion> *add = new list::List<records::DataAboutTheChampion>;           // новый элемент
		insert->next = add;             // указатель предыдущего элемента на новый элемент
		add->value = newChampion;       // инициализаци€ нового элемента
		add->next = end;                // указатель нового элемента к следующему элементу списка
	}
}

void list::freeMemory(list::List<records::DataAboutTheChampion> *begin)       // освобождение пам€ти от списка 
{
	list::List<records::DataAboutTheChampion> *cleaner = begin;        // новый указатель на начало списка

	while (begin)
	{
		cleaner = begin;
		begin = begin->next;
		delete cleaner;
	}
}

void list::deleteCurrentElement(list::List<char> **types, char element)
{
	bool flag = true;
	list::List<char> *del = *types;
	list::List<char> *temp = *types;

	if ((*types)->value == element)
	{
		*types = (*types)->next;
		delete del;
	}
	else
	{
		temp = temp->next;
		while (flag)
		{
			if (temp->value == element)
			{
				del = temp;
				temp = temp->next;
				(*types)->next = temp;
				delete del;
				flag = false;
			}
		}
	}
}