#include "Menu.h"
#include "Gameplay.h"
#include "Instruments.h"

using namespace std;

int main()
{
	system("mode con cols=100 lines=30");
	srand(time(NULL));

	menu::menu();

	return 0;
}