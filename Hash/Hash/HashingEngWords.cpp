#include "HashTableChaining.h"
#include "EngWord.h"
#include <vector>  
#include <crtdbg.h>

#define MAX_WORDS 1000

std::vector<std::string> GetEngWordsFromFile();
const EngWord** GetListOfEngWords();
void CheckIfContaining(HashTableChaining<const EngWord>& table, const EngWord& word);
void Remove(HashTableChaining<const EngWord>& table, const EngWord& word);
int CreateAndPrintHashTableChaining();

////////////////////////////////////////
// TOGGLE ON AND OFF FOR RUNNING	  //
// CAN ONLY RUN ONE HASHTABLE AT ONCE //
////////////////////////////////////////
#define RUN true
#if RUN
int main() { return CreateAndPrintHashTableChaining(); }
#endif
///////////////////////////////////

int CreateAndPrintHashTableChaining()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	HashTableChaining<const EngWord> hashTable(17);
	const EngWord** engwords = GetListOfEngWords();

	// Insertion of EngWords
	for (int i = 0; i < MAX_WORDS; i++)
	{
		if (!engwords[i]) break;
		const EngWord& word = *engwords[i];

		if (hashTable.insert(word))
			printf("%s.\n", word.getWord().c_str());
		else
			printf("COULD NOT PLACE %s.\n", word.getWord().c_str());
	}

	// Information
	printf("\nNumber of collisions: %d.\n", hashTable.getNrOfCollisions());
	printf("Load Factor: %f.\n", hashTable.loadFactor());

	// Testing
	CheckIfContaining	(hashTable, *engwords[4]);
	Remove				(hashTable, *engwords[4]);
	CheckIfContaining	(hashTable, *engwords[4]);

	// Deallocate the courses
	for (size_t i = 0; i < MAX_WORDS; i++)
		if (engwords[i])
			delete engwords[i];

	// Deallocate the ptr to the course pointers
	delete engwords;

	return 0;
}


std::vector<std::string> GetEngWordsFromFile()
{
	FILE *ft;
	int ch;
	std::vector<std::string> lines;

	errno_t error = fopen_s(&ft, "C:/temp/engWords.txt", "r");
	printf("Error: %s\n", strerror(error));

	bool quit = false;
	while (!quit)
	{
		std::string current = "";
		int c = '\0';
		do
		{
			if (c != '\0')
				current.push_back(c);
			c = fgetc(ft);
		} while (c != '\n' && c != EOF);
		if (c == EOF) quit = true;

		lines.push_back(current);
		current.clear();
	}

	fclose(ft);

	return lines;
}

const EngWord** GetListOfEngWords()
{
	const EngWord** engwords;
	engwords = new const EngWord*[MAX_WORDS];
	for (size_t i = 0; i < MAX_WORDS; i++)
		engwords[i] = nullptr;

	int numberOfEngWords = 0;
	std::string word;
	std::vector<std::string> lines = GetEngWordsFromFile();
	for (size_t i = 0; i < lines.size();)
	{
		if (lines[i].empty()) break;

		word = lines[i];					
		i++;

		engwords[numberOfEngWords] = new const EngWord(word);
		numberOfEngWords++;
	}

	return engwords;
}

void CheckIfContaining(HashTableChaining<const EngWord>& table, const EngWord& word)
{
	int index = table.contains(word);

	printf("\nSearching..\n");

	if (index == -1)	printf("Does NOT contain %s.\n", word.getWord().c_str());
	else				printf("Contains %s at index %d\n", word.getWord().c_str(), index);
}

void Remove(HashTableChaining<const EngWord>& table, const EngWord & word)
{
	std::string savedString = word.getWord();

	printf("\nRemoving..\n");
	if (table.remove(word))		printf("Removed word: %s.\n", savedString.c_str());
	else						printf("Could not find %s\n", savedString.c_str());
}