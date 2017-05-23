#include "SortingMethods.h"

/*Упрощенный алгоритм сортировки подсчетом*/
void sorting::countingSort(int count, int *array, int range)
{
	int *c = new int[range];		// Вспомогательный массив для подсчета

	/*Обнуляем вспомогательный массив*/
	for (int i = 0; i < range; i++)
	{
		c[i] = 0;
	}

	/*Подсчитываем кол-во каждого значения в сортируемом массиве
	  и записываем это число в вспомогательный массив в ячейку
	  под индексом этого значения*/
	for (int j = 0; j < count; j++)
	{
		c[array[j]]++;
	}


	int d = 0;

	/*Заполняем сортируемый массив в нужном порядке*/
	for (int j = 0; j < range; j++)
	{
		for (int i = 0; i < c[j]; i++)
		{
			array[d++] = j;
		}
	}

	delete[] c;
}

/*Сортировка подсчетом*/
void sorting::stableCountingSort(int count, int array[], int range)
{
	int *c = new int[range];		// Вспомогательный массив
	int *result = new int[count];	// Результирующий массив

	/*Обноляем вспомогательный массив*/
	for (int i = 0; i < range; i++)
	{
		c[i] = 0;
	}

	/*Заполняем вспомогательный массив*/
	for (int i = 0; i < range; i++)
	{
		for (int j = 0; j < count; j++)
		{
			if (array[j] <= i)
				c[i]++;
		}
	}

	/*Заполняем результирующий массив*/
	for (int i = count - 1; i >= 0; i--)
	{
		c[array[i]]--;
		result[c[array[i]]] = array[i];
	}

	/*Присваиваем сортируемому массиву результирующий*/
	for (int i = 0; i < count; i++)
	{
		array[i] = result[i];
	}

	delete[] result;
	delete[] c;
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