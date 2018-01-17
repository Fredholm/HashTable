#ifndef HASHINGFUNCTIONS_H
#define HASHINGFUNCTIONS_H

#include "HashTableChaining.h"
#include "HashTableLinearProbing.h"
#include "Course.h"
#include "EngWord.h"
#include <vector>
#include <crtdbg.h>
#include <iostream>

// English Words Functions
#define MAX_WORDS			1000
std::vector<std::string>	GetEngWordsFromFile();
const EngWord**				GetListOfEngWords();
void						CheckIfContaining(HashTableChaining<const EngWord>& table, const EngWord& word);
void						Remove(HashTableChaining<const EngWord>& table, const EngWord& word);
int							CreateAndPrintHashTableChaining();

// Courses Functions
#define MAX_COURSES			250 
const Course**				GetCoursesFromFile();
void						CheckIfContaining(HashTableLinearProbing<const Course>& table);
void						RemoveCourse(HashTableLinearProbing<const Course>& table, const Course& word);
int							CreateAndPrintHashTableLinearProbing();

#endif // !HASHINGFUNCTIONS_H
