#include "HashTableLinearProbing.h"
#include "Course.h"
#include <vector>

void CheckIfContaining(HashTableLinearProbing<const Course>& table, const Course& word);

int main()
{
	HashTableLinearProbing<const Course> hashTable(17);

	const Course words[10] =
	{
		Course("DV1923", "Cool Course Name", 7.5f),
		Course("DV5901", "Cool Course Name", 7.5f),
		Course("DV5023", "Cool Course Name", 7.5f),
		Course("DV6912", "Cool Course Name", 7.5f),
		Course("DV5923", "Cool Course Name", 7.5f),
		Course("DV6924", "Cool Course Name", 7.5f),
		Course("DV1111", "Cool Course Name", 7.5f),
		Course("DV2222", "Cool Course Name", 7.5f),
		Course("DV5346", "Cool Course Name", 7.5f),
		Course("DV6200", "Cool Course Name", 7.5f),
	};

	// Insertion of courses
	for (int i = 0; i < 10; i++)
	{
		if (hashTable.insert(words[i]))
			printf("Insertion of %s succesful.\n", words[i].getCode().c_str());
		else
			printf("NONsuccessful insertion of %s.\n", words[i].getCode().c_str());
	}

	printf("Number of collisions: %d.\n", hashTable.getNrOfCollisions());

	// Contains/Searching testing
	CheckIfContaining(hashTable, words[0]);
	const Course fakeWord("DVSHIT", "Bad Course Name", 10.f);
	CheckIfContaining(hashTable, fakeWord);

	printf("\n\nReminder: Don't forget to remove the fucking temp file at C:... (Why?)\n\n");

	return 0;
}

std::vector<std::string> GetContentFromFile()
{
	FILE *ft;
	int ch;
	ft = fopen("C:\temp\courses.txt", "r");
	std::vector<std::string> lines;

	bool quit = false;
	while (quit)
	{
		std::string current = "";
		char c = 0;
		do
		{
			c = getc(ft);
			current.push_back(c);
		} while (c != '\n' && c != EOF);

		lines.push_back(current);
		current.clear();
	}

	fclose(ft);

	return lines;
}

const Course* GetCoursesFromFile()
{
	Course courses[100];
	int numberOfCourses = 0;
	
	std::vector<std::string> lines = GetContentFromFile();
	for (size_t i = 0; i < lines.size(); i++)
	{
		if (lines[i].empty())
			break;

		std::string code = lines[i];
		i++;

		std::string name = lines[i];
		i++;

		float points(atof(lines[i].c_str()));
		i++;

		courses[numberOfCourses] = const Course(code, name, points);
		numberOfCourses++;
	}

	// This is were you left off
	return &courses;
}

void CheckIfContaining(HashTableLinearProbing<const Course>& table, const Course& word)
{
	int index = table.contains(word);
	
	printf("\nSearching..\n");

	if (index == -1)	printf("Does NOT contain %s.\n", word.getCode().c_str());
	else				printf("Contains %s at index %d\n", word.getCode().c_str(), index);
}