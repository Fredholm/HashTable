#ifndef HASHTABLE_H
#define HASHTABLE_H

template <typename HashElement>
class HashTable
{
private:
	// internal datastructure

	int nrOfCollisions;
	int hashTableSize;
	int myHash(const HashElement& elem) const
	{
		static Hash<HashElement> hashFunc;
		return hashFunc(elem) % hasTableSize; // hashFunc(elem) is a call of the defined operator() for HashElement
	}
public:
	HashTable(int hashTableSize = 17);
	HashTable(const HashTable& aTable);
	virtual ~HashTable();
	HashTable& operator=(const HashTable& aTable);
	int contains(const HashElement& elem) const; // returns index or -1
	bool insert(const HashElement& elem);
	bool remove(const HashElement& elem);
	HashElement& get(int index) const;
	void makeEmpty();
	double loadFactor() const;
	int getNrOfElements() const;
	int getNrOfCollisions() const;
	void resetNrOfCollisions();

};

#endif