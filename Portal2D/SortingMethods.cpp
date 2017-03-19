#include "SortingMethods.h"

void sorting::countingSort(int count, int arrName[], int range)
{
	int *c = new int[range];

	for (int null = 0; null < range; null++)
	{
		c[null] = 0;
	}

	for (int j = 0; j < count; j++)
	{
		c[arrName[j]]++;
	}

	int d = 0;

	for (int j = 0; j < range; j++)
		for (int i = 0; i < c[j]; i++)
			arrName[d++] = j;
	delete[] c;
}

void sorting::stableCountingSort(int count, int arrName[], int range)		// Следует изменить
{
	int *c = new int[range];
	int *result = new int[count];

	for (int null = 0; null < range; null++)
	{
		c[null] = 0;
	}

	for (int i = 0; i < range; i++)
	{

		for (int j = 0; j < count; j++)
		{
			if (arrName[j] <= i)
				c[i]++;
		}
	}

	for (int i = count - 1; i >= 0; i--)
	{
		c[arrName[i]] = c[arrName[i]] - 1;
		result[c[arrName[i]]] = arrName[i];
	}

	for (int i = 0; i > count; i++)
	{
		arrName[i] = result[i];
	}

	delete[] result;
	delete[] c;
}

void sorting::bubbleSortForList(list::List<records::DataAboutTheChampion> *begin)
{
	list::List<records::DataAboutTheChampion> *sort = begin;
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