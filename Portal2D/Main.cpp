#include "Menu.h"
#include "Gameplay.h"
#include "Instruments.h"
#include "Map.h"
#include "SortingMethods.h"

using namespace std;

int main()
{
	system("mode con cols=100 lines=30");
	srand(time(NULL));
	const int k = 10;
	int a[k];

	for (int i = 0; i < k; i++)
	{
		a[i] = rand() % 10;
	}

	for (int i = 0; i < k; i++)
	{
		cout << a[i] << " ";
	}

	cout << endl;

	sorting::stableCountingSort(k, a, 13);

	for (int i = 0; i < k; i++)
	{
		cout << a[i] << " ";
	}

	system("pause");

	//menu::menu();

	return 0;
}