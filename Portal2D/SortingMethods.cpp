#include "SortingMethods.h"

using namespace std;

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

void sorting::selectionSort(int* arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		int min_index = i;

		for (int j = i + 1; j < size; j++)
		{
			if (arr[j] < arr[min_index])
			{
				min_index = j;
			}
		}

		if (min_index != i)
		{
			swap(arr[i], arr[min_index]);
		}
	}

	cout << endl;
}

void sorting::bubbleSort(int* arr, int size)
{
	bool exit = false;

	while (!exit)
	{
		exit = true;

		for (int i = 0; i < size - 1; i++)
		{
			if (arr[i] > arr[i + 1])
			{
				swap(arr[i], arr[i + 1]);
				exit = false;
			}
		}
	}
}

void sorting::coctailSort(int *arr, int size)
{
	int leftMark = 0;
	int rightMark = size - 1;
	bool exit = false;

	while (!exit)
	{
		exit = true;
		for (int i = rightMark; i > leftMark; i--)
		{
			if (arr[i] < arr[i - 1])
			{
				swap(arr[i], arr[i - 1]);
				exit = false;
			}
		}
		leftMark++;

		for (int i = leftMark; i < rightMark; i++)
		{
			if (arr[i] > arr[i + 1])
			{
				swap(arr[i], arr[i + 1]);
				exit = false;
			}
		}
		rightMark--;
	}
}

void sorting::insertionSort(int* arr, int size)
{
	int i, j;
	for (i = 1; i < size; i++)
	{
		int temp = arr[i];
		for (j = i - 1; j >= 0 && temp < arr[j]; j--)
		{
			arr[j + 1] = arr[j];
		}
		arr[j + 1] = temp;
	}
}

void sorting::shellSort(int* arr, int size)
{
	int i, j;
	int step = size / 2;

	while (step > 0)
	{
		for (i = step; i < size; i++)
		{
			int temp = arr[i];
			for (j = i - step; j >= 0 && temp < arr[j]; j -= step)
			{
				arr[j + step] = arr[j];
			}
			arr[j + step] = temp;
		}
		step = step / 2;
	}
}

void sorting::quickSort(int* arr, int left, int right)
{
	int i = left;
	int j = right;
	int x = arr[(i + j) / 2];

	while (i <= j)
	{
		while (x > arr[i])
		{
			i++;
		}
		while (x < arr[j])
		{
			j--;
		}
		if (i <= j)
		{
			swap(arr[i], arr[j]);
			i++;
			j--;
		}
	}

	if (i < right)
	{
		quickSort(arr, i, right);
	}
	if (j > left)
	{
		quickSort(arr, left, j);
	}

}

void sorting::merge(int* arr, int left, int right)
{
	int i = left;
	int mid = (left + right) / 2;
	int j = mid + 1;
	int* result = new int[right];
	int k = 0;

	while (i <= mid && j <= right)
	{
		if (arr[i] <= arr[j])
		{
			result[k] = arr[i];
			i++;
		}
		else
		{
			result[k] = arr[j];
			j++;
		}
		k++;
	}
	while (i <= mid)
	{
		result[k] = arr[i];
		i++;
		k++;
	}
	while (j <= mid)
	{
		result[k] = arr[j];
		j++;
		k++;
	}

	for (int i = 0; i < k; i++)
	{
		arr[left + i] = result[i];
	}
}

void sorting::mergeSort(int* arr, int left, int right)
{
	if (left < right)
	{
		if (right - left == 1)
		{
			if (arr[left] > arr[right])
			{
				swap(arr[left], arr[right]);
			}
		}
		else
		{
			int middle = (left + right) / 2;
			mergeSort(arr, left, middle);
			mergeSort(arr, middle + 1, right);
			merge(arr, left, right);
		}
	}
}

void sorting::countingSort(int* arr, int size, int range)
{
	int* c = new int[range];
	int* result = new int[size];

	for (int i = 0; i < range; i++)
	{
		c[i] = 0;
	}

	for (int i = 0; i < range; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (arr[j] <= i)
			{
				c[i]++;
			}
		}
	}

	for (int i = size - 1; i >= 0; i--)
	{
		c[arr[i]]--;
		result[c[arr[i]]] = arr[i];
	}

	for (int i = 0; i < size; i++)
	{
		arr[i] = result[i];
	}

	delete[] result;
	delete[] c;
}


void sorting::linearSearch(int* arr, int size, int key)
{
	bool success = false;
	for (int i = 0; i < size; i++)
	{
		if (arr[i] == key)
		{
			cout << "Key in cell number " << i << endl;
			success = true;
		}
	}
	if (!success)
	{
		cout << "Key not found" << endl;
	}
}

void sorting::binarySearch(int* arr, int size, int key)
{
	int left = -1;
	int right = size + 1;

	while (left < right - 1)
	{
		int mid = (left + right) / 2;
		if (arr[mid] > key)
		{
			right = mid;
		}
		else
		{
			left = mid;
		}
	}

	if (left >= 0 && arr[left] == key)
	{
		cout << "Key in cell number " << left << endl;
	}
	else
	{
		cout << "Key not found" << endl;
	}
}

void sorting::kmpMatcher(char* text, char* pattern)
{
	int i, j;
	int stringLength = strlen(text);
	int patternLenghth = strlen(pattern);
	int* arrayForPrefix = new int[patternLenghth];	// массив со значением префикса
	bool isSubstringFound = false;

	arrayForPrefix[0] = 0;
	// вычисение префикс-функции
	for (i = 1, j = 0; i < patternLenghth; i++)
	{
		while (j > 0 && pattern[i] != pattern[j])
		{
			j = arrayForPrefix[j - 1];
		}
		if (pattern[i] == pattern[j])
		{
			j++;
		}
		arrayForPrefix[i] = j;
	}
	// поиск
	for (i = 0, j = 0; (i < stringLength) && (!isSubstringFound); i++)
	{
		while (j > 0 && pattern[j] != text[i])
		{
			j = arrayForPrefix[j - 1];
		}
		if (pattern[j] == text[i])
		{
			j++;
		}
		if (j == patternLenghth)
		{
			isSubstringFound = true;
		}
	}

	if (isSubstringFound)
	{
		cout << "Substring found!" << endl;
	}
	else
	{
		cout << "Substring not found!" << endl;
	}

	delete[] arrayForPrefix;
}