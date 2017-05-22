#include "List.h"
#include "Definitions.h"

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

void list::deleteCurrentElement(list::List<char> **types, char element)
{
	bool flag = true;
	list::List<char> *del = *types;
	list::List<char> *temp = del->next;

	if ((*types)->value == element)
	{
		*types = (*types)->next;
		delete del;
	}
	else
	{
		while (flag)
		{
			temp = del;
			del = del->next;
			if (del->value == element)
			{
				temp->next = del->next;
				delete del;
				flag = false;
			}
		}
	}
}