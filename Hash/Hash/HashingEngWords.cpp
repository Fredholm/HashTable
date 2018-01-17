#include "HashingFunctions.h"

int CreateAndPrintHashTableChaining()
{
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

	// Write a Sentence and print results
	WriteSentence(hashTable);

	// Deallocate the courses
	for (size_t i = 0; i < MAX_WORDS; i++)
		if (engwords[i])
			delete engwords[i];

	// Deallocate the ptr to the course pointers
	delete engwords;

	printf("Going back to main menu.\n\n\n");

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

void WriteSentence(HashTableChaining<const EngWord>& table)
{
	// Going to the end of buffer to avoid overlapping text into cin
	fseek(stdin, 0, SEEK_END);

	// Get input from user
	std::string str;
	printf("\nWrite a sentence: ");
	std::getline(std::cin, str);

	std::vector<std::string> words;
	std::string current = "";

	// Build all the words out of sentece
	bool dot = false;
	for (size_t i = 0; i < str.size(); i++) 
	{
		// Word Complete
		if (str[i] == ' ')
		{
			words.push_back(current);
			current.clear();
		}
		else if (str[i] == '.')
		{
			dot = true;
			words.push_back(current);
			current.clear();
		}
		else
		{
			current.push_back(str[i]);
		}
	}
	if (!dot)
		words.push_back(current);

	int counter = 0;
	for (std::string& s : words)
	{
		const EngWord search(s);
		if (table.contains(search) != -1)
			counter++;

		printf("Inputted word: %s\n", s.c_str());
	}

	printf("\nResult!\n%d words were found in the table. Of the total %d in your sentence.\n\n", counter, words.size());
}