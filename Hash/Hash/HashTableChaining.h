#ifndef HASHTABLECHAINING_H
#define HASHTABLECHAINING_H

#include "Hash.h"

template <typename HashElement>
struct HashNode
{
	HashNode(HashElement* elem)
	{
		data = elem;
		next = nullptr;
	}

	HashElement* data;
	HashNode<HashElement>* next;
};

template <typename HashElement>
class HashTableChaining
{
public:
	HashTableChaining(int hashTableSize = 17)
	{
		this->nrOfElements = 0;
		this->nrOfCollisions = 0;
		this->hashTableSize = hashTableSize;

		nodes = new HashNode<HashElement>*[hashTableSize];
		for (int i = 0; i < hashTableSize; i++)
			nodes[i] = nullptr;
	}

	HashTableChaining(const HashTableChaining& aTable)
	{
		this->nrOfElements = aTable.getNumberOfElements();
		this->nrOfCollisions = aTable.getNumberOfCollisions();
		this->hashTableSize = aTable.getHashTableSize();

		nodes = new HashNode<HashElement>*[hashTableSize];
		HashNode<HashElement>** otherNodes = aTable.getNodes();
		for (int i = 0; i < hashTableSize; i++)
		{
			if (otherNodes[i])
			{
				nodes[i] = otherNodes[i];

				HashNode<HashElement>* traveler = otherNodes[i];
				while (traveler->next)
				{
					nodes[i]->next = traveler->next;
					nodes[i] = nodes[i]->next;
					nodes[i]->data = traveler->next->data;
					traveler = traveler->next;
				}
			}
		}
	}

	virtual ~HashTableChaining()
	{
		makeEmpty();

		delete nodes;
		nodes = nullptr;
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
		nodes = new HashNode<HashElement>*[hashTableSize];
		HashNode<HashElement>** otherNodes = aTable.getNodes();
		for (int i = 0; i < hashTableSize; i++)
		{
			if (otherNodes[i])
			{
				nodes[i] = otherNodes[i];

				HashNode<HashElement>* traveler = otherNodes[i];
				while (traveler->next)
				{
					nodes[i]->next = traveler->next;
					nodes[i] = nodes[i]->next;
					nodes[i]->data = traveler->next->data;
					traveler = traveler->next;
				}
			}
		}

		return this;
	}

	int contains(const HashElement& elem) const // returns index or -1
	{
		int hashIndex = myHash(elem);

		HashNode<HashElement>* traveler = nodes[hashIndex];

		// No Resulting hashnode
		if (!traveler)
			return false;

		// Searching
		do
		{
			if (*traveler->data == elem)
			{
				return hashIndex;
			}
			if (traveler->next) traveler = traveler->next;
		} while (traveler->next != nullptr);

		return -1;
	}

	bool insert(const HashElement& elem)
	{
		int hashIndex = myHash(elem);

		// No Collision
		if (!nodes[hashIndex])
		{
			nrOfElements++;
			printf("Inserting on Index: %d \t\t\t: ", hashIndex);
			nodes[hashIndex] = new HashNode<HashElement>(&elem);
			return true;
		}
		// Collision
		else
		{
			nrOfElements++;
			nrOfCollisions++;
			printf("Collided - Inserting on Index: %d \t: ", hashIndex);
			HashNode<HashElement>* traveler = nodes[hashIndex];
			while (traveler->next != nullptr)
			{
				traveler = traveler->next;
			}

			// Collision solved
			traveler->next = new HashNode<HashElement>(&elem);
			return true;
		}

		// No spots left; Should not be possible with chaining, something went wrong
		return false;
	}

	bool remove(const HashElement& elem)
	{
		int hashIndex = myHash(elem);

		HashNode<HashElement>* traveler = nodes[hashIndex];
		
		// No Resulting hashnode
		if (!traveler) 
			return false;

		// Searching
		do 
		{
			if (traveler->data == &elem)
			{
				// Remove and replace with the next in line
				HashNode<HashElement>* next = traveler->next;
				delete traveler;
				nodes[hashIndex] = next;
				return true;
			}
			traveler = traveler->next;
		} while (traveler->next != nullptr);

		// Should not be possible with chaining, something went wrong
		return false;
	}

	HashElement& get(int index) const
	{
		return nullptr;
	}

	void makeEmpty()
	{
		for (size_t i = 0; i < hashTableSize; i++)
		{
			HashNode<HashElement>* traveler = nodes[i];
			while (traveler)
			{
				HashNode<HashElement>* temp = traveler->next;
				delete traveler;
				traveler = nullptr;
				traveler = temp;
			}
		}

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

	HashNode<HashElement>** getNodes()
	{
		return nodes;
	}

private:

	HashNode<HashElement>** nodes;

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
