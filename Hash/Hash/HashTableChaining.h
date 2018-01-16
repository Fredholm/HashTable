#ifndef HASHTABLECHAINING_H
#define HASHTABLECHAINING_H

#include "Hash.h"

template <typename HashElement>
class HashTableChaining
{
public:

	HashTableChaining(int hashTableSize = 17)
	{
		nrOfElements = 0;
		nrOfCollisions = 0;

		this->hashTableSize = hashTableSize;
		table = new HashElement*[hashTableSize];
		for (int i = 0; i < hashTableSize; i++)
			table[i] = nullptr;
	}

	HashTableChaining(const HashTableChaining& aTable)
	{
		nrOfElements = 0;
		nrOfCollisions = 0;

		this->hashTableSize = aTable.getNrOfElements();
		table = new HashElement*[hashTableSize];

		for (int i = 0; i < hashTableSize; i++)
			table[i] = aTable.get(i);
	}

	virtual ~HashTableChaining()
	{
		makeEmpty();
		delete table;
	}

	HashTableChaining& operator=(const HashTableChaining& aTable)
	{
		// Delete current
		if (table != nullptr)
		{
			makeEmpty();
			delete table;
		}

		// Copy the new one
		return this;
	}

	int contains(const HashElement& elem) const // returns index or -1
	{
		int hashIndex = myHash(elem);

		if (table[hashIndex] == nullptr)
			return -1;

		if (table[hashIndex] != &elem)
			return -1;

		return hashIndex;
	}

	bool insert(const HashElement& elem)
	{
		int hashIndex = myHash(elem);
		printf("Inserting on Index: %d \t: ", hashIndex);

		if (table[hashIndex] == nullptr)
		{
			// No collision
			table[hashIndex] = &elem;
			return true;
		}
		else
		{
			// Collision
			int start = hashIndex;
			int counter = hashIndex + 1;
			while (start != counter)
			{
				if (counter >= hashTableSize)
					counter = 0;

				if (table[counter] == nullptr)
				{
					table[counter] = &elem;
					nrOfCollisions++;

					printf("Collided\nTrying..\nInserting on Index: %d \t: ", counter);
					return true;
				}

				counter++;
			}
		}

		// The Hashtable is completly filled
		return false;
	}

	bool remove(const HashElement& elem)
	{
		int hashIndex = myHash(elem);

		if (table[hashIndex] != nullptr)
		{
			// Remove element
			table[hashIndex] = nullptr;
			return true;
		}

		// Element wasn't found, nothing got removed
		return false;
	}

	HashElement& get(int index) const
	{
		return table[index];
	}

	void makeEmpty()
	{
		for (int i = 0; i < hashTableSize; i++)
			table[i] = nullptr;

		nrOfElements = 0;
		nrOfCollisions = 0;
	}

	double loadFactor() const
	{
		return nrOfElements / hashTableSize;
	}

	int getNrOfElements() const
	{
		return nrOfElements;
	}

	int getNrOfCollisions() const
	{
		return nrOfCollisions;
	}

	void resetNrOfCollisions()
	{
		nrOfCollisions = 0;
	}

private:
	HashElement * * table;
	int nrOfElements;
	int nrOfCollisions;
	int hashTableSize;
	int myHash(const HashElement& elem) const
	{
		static Hash<HashElement> hashFunc;
		return hashFunc(elem) % hashTableSize; // hashFunc(elem) is a call of the defined operator() for HashElement
	}
};


#endif // !HASHTABLECHAINING_H
