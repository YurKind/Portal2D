#include "List.h"
#include "Definitions.h"

void list::addInCertainPlace(list::List<records::DataAboutTheChampion> **list, int placeNumber, records::DataAboutTheChampion newChampion)       // вставка элемента списка с новым рекордсменом на соответствующее место 
{
	if (placeNumber == 0)
	{
		list::addBegin(list, newChampion);           // вставка в начало списка
	}
	else
	{
		list::List<records::DataAboutTheChampion> *insert = *list;         // новый указатель на начало списка

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
	bool isCurrentElementFound = true;
	list::List<char> *del = *types;
	list::List<char> *temp = del->next;

	//если указанный элемент совпал с элементом в списке
	if ((*types)->value == element)	
	{
		*types = (*types)->next;
		delete del;
	}
	else
	{
		// пока не найден указанный элемент или не достигли конца списка
		while (isCurrentElementFound)
		{
			temp = del;
			del = del->next;
			//если указанный элемент совпал с элементом в списке
			if (del->value == element)
			{
				temp->next = del->next;
				delete del;
				isCurrentElementFound = false;
			}
		}
	}
}