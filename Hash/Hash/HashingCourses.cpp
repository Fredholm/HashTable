#include "HashingFunctions.h"

int CreateAndPrintHashTableLinearProbing()
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

	// Information
	printf("\nNumber of collisions: %d.\n", hashTable.getNrOfCollisions());
	printf("Load Factor: %f.\n", hashTable.loadFactor());

	// Contains/Searching testing
	CheckIfContaining	(hashTable);
	RemoveCourse		(hashTable, *courses[0]);
	CheckIfContaining	(hashTable);

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

	errno_t error = fopen_s(&ft, "C:/temp/courses.txt", "r");
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

const Course** GetCoursesFromFile()
{
	const Course** courses;
	courses = new const Course*[MAX_COURSES];
	for (size_t i = 0; i < MAX_COURSES; i++)
		courses[i] = nullptr;

	int numberOfCourses = 0;	
	float points;
	std::string code, name;
	std::vector<std::string> lines = GetContentFromFile();
	for (size_t i = 0; i < lines.size();)
	{
		if (lines[i].empty()) break;

		code	= lines[i];					i++;
		name	= lines[i];					i++;
		points	= atof(lines[i].c_str());	i++;

		courses[numberOfCourses] = new const Course(code, name, points);
		numberOfCourses++;
	}

	return courses;
}

void CheckIfContaining(HashTableLinearProbing<const Course>& table)
{
	char input[24];
	printf("Check if hashtable contains: ");
	std::cin >> input; 

	const Course course(input, "temp", 0.5f);
	int index = table.contains(course);
	
	printf("\nSearching..\n");

	if (index == -1)	printf("Does NOT contain %s.\n", course.getCode().c_str());
	else				printf("Contains %s at index %d\n", course.getCode().c_str(), index);
}

void RemoveCourse(HashTableLinearProbing<const Course>& table, const Course& word)
{
	std::string savedString = word.getCode();

	printf("\nRemoving..\n");
	if (table.remove(word))		printf("Removed course: %s.\n", savedString.c_str());
	else						printf("Could not find %s\n", savedString.c_str());
}