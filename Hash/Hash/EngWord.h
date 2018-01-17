#ifndef ENGWORD_H
#define ENGWORD_H

#include "Hash.h"
#include <string>

class EngWord
{
public:
	EngWord()						{ word = "";			}
	EngWord(std::string inWord)		{ word = inWord;		}	
	EngWord(const EngWord& aTable)	{ word = aTable.word;	}
	virtual ~EngWord()				{ word.clear();			}

	// Gets and Sets
	std::string getWord() const { return word; }
	void setWord(std::string inWord) { word = inWord; }

	// Equal Operations
	bool operator==(const EngWord& aTable) const { return (strcmp(word.c_str(), aTable.word.c_str()) == 0); }
	bool operator!=(const EngWord& aTable) const { return (strcmp(word.c_str(), aTable.word.c_str()) != 0); }

private:
	std::string word;
};

template<>
class Hash<const EngWord>
{
public:
	int operator()(const EngWord& elem) const
	{
		size_t hash = std::hash<std::string>{}(elem.getWord());
		return abs(int(hash));
	}
};

#endif //!ENGWORD