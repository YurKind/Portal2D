#include "Records.h"

void records::records()
{
	char* buff = "";
	std::ifstream fin("Records.txt");
	fin >> buff;
	std::cout << buff;
}

