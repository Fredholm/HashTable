#ifndef HASHTABLELINEARPROBING_H
#define HASHTABLELINEARPROBING_H

#include "Hash.h"

template <typename HashElement>
class HashTableLinearProbing
{
public:
	HashTableLinearProbing(int hashTableSize = 17)
	{
		this->nrOfElements = 0;
		this->nrOfCollisions = 0;
		this->hashTableSize = hashTableSize;

		table = new HashElement*[hashTableSize];
		for (int i = 0; i < hashTableSize; i++)
			table[i] = nullptr;
	}

	HashTableLinearProbing(const HashTableLinearProbing& aTable)
	{
		this->nrOfElements = aTable.getNrOfElements();
		this->nrOfCollisions = aTable.getNrOfCollisions();
		this->hashTableSize = aTable.getHashTableSize();

		table = new HashElement*[hashTableSize];

		for (int i = 0; i < hashTableSize; i++)
			table[i] = aTable.get(i);
	}

	virtual ~HashTableLinearProbing()
	{
		makeEmpty();
		delete table;
	}

	HashTableLinearProbing& operator=(const HashTableLinearProbing& aTable)
	{
		// Delete current
		if (table != nullptr)
		{
			makeEmpty();
			delete table;
		}

		// Create new
		this->nrOfElements = aTable.getNrOfElements();
		this->nrOfCollisions = aTable.getNrOfCollisions();
		this->hashTableSize = aTable.getHashTableSize();
		table = new HashElement*[hashTableSize];
		for (int i = 0; i < hashTableSize; i++)
			table[i] = aTable.get(i);

		// Copy the new one
		return this;
	}

	int contains(const HashElement& elem) const // returns index or -1
	{
		int hashIndex = myHash(elem);

		// Checking from start hashIndex to find the element
		int counter = hashIndex;
		int loop = 0;
		while (loop <= hashTableSize)
		{
			// Loop at end of table
			if (counter >= hashTableSize)
				counter = 0;

			// Found it!
			if (table[counter] == &elem)
				return counter;

			counter++;
			loop++;
		}
		
		return -1;
	}

	bool insert(const HashElement& elem)
	{
		int hashIndex = myHash(elem);
		printf("Inserting on Index: %d \t: ", hashIndex);
		nrOfElements++;

		if (table[hashIndex] == nullptr)
		{
			// No collision
			table[hashIndex] = &elem;
			return true;
		}
		else
		{
			// Collision
			int counter = hashIndex;
			int loop = 0;
			while (loop <= hashTableSize)
			{
				// Loop at end of table
				if (counter >= hashTableSize)
					counter = 0;

				// Found a empty spot
				if (table[counter] == nullptr)
				{
					table[counter] = &elem;
					nrOfCollisions++;

					printf("Collided\nTrying..\nInserting on Index: %d \t: ", counter);
					return true;
				}

				counter++;
				loop++;
			}
		}

		// The Hashtable is completly filled
		nrOfElements--;
		return false;
	}

	bool remove(const HashElement& elem)
	{
		int hashIndex = myHash(elem);

		int counter = hashIndex;
		int loop = 0;
		while (loop <= hashTableSize)
		{
			// Loop at end of table
			if (counter >= hashTableSize)
				counter = 0;

			// Remove the correct element
			if (table[counter] == &elem)
			{	
				table[counter] = nullptr;
				return true;
			}

			counter++;
			loop++;
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
		return float(nrOfElements) / hashTableSize;
	}

	int getNrOfElements() const
	{
		return nrOfElements;
	}

	int getNrOfCollisions() const
	{
		return nrOfCollisions;
	}

	int getHashTableSize() const
	{
		return hashTableSize;
	}

	void resetNrOfCollisions()
	{
		nrOfCollisions = 0;
	}

private:
	HashElement** table;
	int nrOfElements;
	int nrOfCollisions;
	int hashTableSize;
	int myHash(const HashElement& elem) const
	{
		static Hash<HashElement> hashFunc;
		return hashFunc(elem) % hashTableSize; // hashFunc(elem) is a call of the defined operator() for HashElement
	}
};


#endif // !HASHTABLELINEARPROBING_H