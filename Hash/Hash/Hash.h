#ifndef HASH_H
#define HASH_H

template <typename Key>
class Hash
{
public:
	virtual int operator()(const Key & key) const
	{
		return 0;
	}
};


#endif