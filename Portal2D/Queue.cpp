#include "Queue.h"
#include "Definitions.h"

void initializesArrayWithDifferentNumbers(int *arr) 
{
	for (int i = 0; i < NUMBER_OF_LEVELS; i++)
	{
		bool flag = true;
		int temp = rand() % NUMBER_OF_LEVELS + 1;
		for (int j = 0; j < NUMBER_OF_LEVELS; j++)
		{
			if (temp == arr[j])
			{
				i--;
				flag = false;
			}
		}

		if (flag)
		{
			arr[i] = temp;
		}
	}
}
