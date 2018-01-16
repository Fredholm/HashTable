#include "HashTableLinearProbing.h"
#include "Course.h"
#include <vector>

#define MAX_COURSES 250 

const Course** GetCoursesFromFile();
void CheckIfContaining(HashTableLinearProbing<const Course>& table, const Course& word);

int main()
{
	HashTableLinearProbing<const Course> hashTable(17);

	const Course** courses = GetCoursesFromFile();

	// Insertion of courses
	for (int i = 0; i < MAX_COURSES; i++)
	{
		if (!courses[i]) break;
		const Course& course = *courses[i];

		if (hashTable.insert(course))
			printf("Insertion of %s succesful.\n", course.getCode().c_str());
		else
			printf("NONsuccessful insertion of %s.\n", course.getCode().c_str());
	}

	printf("Number of collisions: %d.\n", hashTable.getNrOfCollisions());

	// Contains/Searching testing
	CheckIfContaining(hashTable, *courses[0]);
	const Course fakeWord("DVSHIT", "Bad Course Name", 10.f);
	CheckIfContaining(hashTable, fakeWord);

	printf("\n\nReminder: Don't forget to remove the fucking temp file at C:... (Why?)\n\n");

	// Deallocate the courses
	for (size_t i = 0; i < MAX_COURSES; i++)
		if (courses[i])
			delete courses[i];

	// Deallocate the ptr to the course pointers
	delete courses;

	return 0;
}


std::vector<std::string> GetContentFromFile()
{
	FILE *ft;
	int ch;
	std::vector<std::string> lines;

	errno_t error = fopen_s(&ft, "C:\temp\courses.txt", "r");
	printf("Error: %s\n", strerror(error));

	bool quit = false;
	while (!quit)
	{
		std::string current = "";
		int c;
		do
		{
			c = fgetc(ft);
			current.push_back(c);
		} while (c != '\n' && c != EOF);
		if (c == EOF) quit = true;

		lines.push_back(current);
		current.clear();
	}

	fclose(ft);

	return lines;
}

const Course** GetCoursesFromFile()
{
	const Course** courses;
	courses = new const Course*[MAX_COURSES];
	for (size_t i = 0; i < MAX_COURSES; i++)
		courses = nullptr;

	int numberOfCourses = 0;
	
	float points;
	std::string code, name;
	std::vector<std::string> lines = GetContentFromFile();
	for (size_t i = 0; i < lines.size(); i++)
	{
		if (lines[i].empty())
			break;

		code = lines[i];
		i++;

		name = lines[i];
		i++;

		points = atof(lines[i].c_str());
		i++;

		courses[numberOfCourses] = new Course(code, name, points);
		numberOfCourses++;
	}

	return courses;
}

void CheckIfContaining(HashTableLinearProbing<const Course>& table, const Course& word)
{
	int index = table.contains(word);
	
	printf("\nSearching..\n");

	if (index == -1)	printf("Does NOT contain %s.\n", word.getCode().c_str());
	else				printf("Contains %s at index %d\n", word.getCode().c_str(), index);
}