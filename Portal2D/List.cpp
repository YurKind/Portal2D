#include "List.h"

void list::addList(list::List<records::DataAboutTheChampion> **begin, std::ifstream &fin)          // создание и инициализация списка
{
	list::List<records::DataAboutTheChampion> *add = *begin;
	std::ifstream finForSize(FILE_NAME_RECORDS);
	char *buf = NULL;
	while (!fin.eof())
	{
		int lengthLine = records::countLengthLine(finForSize);     // узнаем длинну строки для объявления массива-буфера
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

template<class T1, class T2>
void list::addBegin(T1 **begin, T2 insertable)        // вставка в начало списка
{
	T1 *add = new T1;
	add->value = insertable;
	add->next = *begin;
	*begin = add;
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
			insert = insert->next;      // передвигаемся до нужного места
		}
		list::List<records::DataAboutTheChampion> *end = insert->next;       // указатель на элемент на который будет ссылаться новый элемент списка 
		list::List<records::DataAboutTheChampion> *add = new list::List<records::DataAboutTheChampion>;           // новый элемент
		insert->next = add;             // указатель предыдущего элемента на новый элемент
		add->value = newChampion;       // инициализация нового элемента
		add->next = end;                // указатель нового элемента к следующему элементу списка
	}
}

void list::freeMemory(list::List<records::DataAboutTheChampion> *begin)       // освобождение памяти от списка 
{
	list::List<records::DataAboutTheChampion> *cleaner = begin;        // новый указатель на начало списка
	while (begin)
	{
		cleaner = begin;
		begin = begin->next;
		delete cleaner;
	}
}

template <class T1, class T2>
void list::deleteCurrentElement(list::List<T1> *types, T2 element)
{
	T1 *del = types;
	T1 *delNext = del->next;

	while (delNext->next != EMPTY_SPACE)
	{
		if (delNext == element)
		{
			del->next = delNext->next;
		}

		del = delNext;
		delNext = delNext->next;
	}
}

template <typename T>
T list::peek(List<T>* types)
{

	T top = types->element;
	return top;
}
