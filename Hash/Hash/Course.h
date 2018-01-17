#ifndef COURSE_H
#define COURSE_H

#include "Hash.h"
#include <string>

class Course
{
public:
	Course() { name = code = ""; points = 0; }
	Course(std::string inCode, std::string inName, float inPoints) { code = inCode; name = inName; points = inPoints; }
	Course(const Course& aTable) { code = aTable.code; name = aTable.name; points = aTable.points; }
	virtual ~Course() { }

	// Gets and Sets
	std::string getCode() const { return code; }
	std::string getName() const { return name; }
	float getPoints() const { return points; }
	void setCode(std::string inCode) { code = inCode; }
	void setName(std::string inName) { name = inName; }
	void setPoints(float inPoints) { points = inPoints; }

	// Equal Operations (because the code for each course is enough, we only need to compare that)
	bool operator==(const Course& other) const { return (strcmp(code.c_str(), other.code.c_str()) == 0); }
	bool operator!=(const Course& other) const { return (strcmp(code.c_str(), other.code.c_str()) != 0); }

private:
	std::string code;	// Unique
	std::string name;
	float		points;
};

template<>
class Hash<const Course>
{
public:
	int operator()(const Course& elem) const
	{
		size_t hash = std::hash<std::string>{}(elem.getCode());
		return abs(int(hash));
	}
};

#endif //!COURSE_H