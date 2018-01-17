#include "HashingFunctions.h"

char getInput()
{
	char input;
	printf("1. Hashtable Chaining.\n2. Hashtable Linear Probing.\n3. Quit\nInput: ");
	std::cin >> input;
	return input;
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	bool quit = false;
	while (!quit)
	{
		switch (getInput())
		{
		case '1': CreateAndPrintHashTableChaining();		break;
		case '2': CreateAndPrintHashTableLinearProbing(); break;
		case '3': quit = true; break;
		default: break;
		}
	}
	
	return 0;
}