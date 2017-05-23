#include "SortingMethods.h"

void sorting::countingSort(int count, int *array, int range)
{
	int *c = new int[range];

	for (int i = 0; i < range; i++)
	{
		c[i] = 0;
	}

	for (int j = 0; j < count; j++)
	{
		c[array[j]]++;
	}

	int d = 0;

	for (int j = 0; j < range; j++)
	{
		for (int i = 0; i < c[j]; i++)
		{
			array[d++] = j;
		}
	}

	delete[] c;
}

void sorting::stableCountingSort(int count, int array[], int range)
{
	int *c = new int[range];
	int *result = new int[count];

	for (int i = 0; i < range; i++)
	{
		c[i] = 0;
	}

	for (int i = 0; i < range; i++)
	{

		for (int j = 0; j < count; j++)
		{
			if (array[j] <= i)
				c[i]++;
		}
	}

	for (int i = count - 1; i >= 0; i--)
	{
		c[array[i]]--;
		result[c[array[i]]] = array[i];
	}

	for (int i = 0; i < count; i++)
	{
		array[i] = result[i];
	}

	delete[] result;
	delete[] c;
}

void sorting::bubbleSortForList(list::List<records::DataAboutTheChampion> *list)
{
	list::List<records::DataAboutTheChampion> *sort = list;
	int swap = 1;
	while (swap != 0)
	{
		swap = 0;
		while (sort->next)
		{
			if (sort->value.score > sort->next->value.score)
			{
				records::DataAboutTheChampion temp = sort->value;
				sort->value = sort->next->value;
				sort->next->value = temp;
				swap++;
			}
			sort = sort->next;
		}
	}
}

void sort(list::List<records::DataAboutTheChampion> *root)
{
	list::List<records::DataAboutTheChampion> *p, *key;
	list::List<records::DataAboutTheChampion> *result = root;
	root = root->next;      /* Головой стал следующий элемент */
	result->next = NULL;    /* Первый элемент отсортированного списка */

	while (root->next != NULL) 
	{
		key = root;
		root = root->next;

		if (key->value.score < result->value.score)
		{   /* Вставляем результат в голову */
			key->next = result;
			result = key;
		}
		else 
		{
			p = result;
			while (p->next != NULL)
			{     
				if (p->next->value.score > key->value.score) 
					break;

				p = p->next;
			}
			key->next = p->next;
			p->next = key;
		}
	}

	root = result;
}