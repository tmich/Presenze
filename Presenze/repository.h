#pragma once
#include <vector>

template<typename E>
class Repository
{
public:
	virtual E get(int) = 0;
	virtual void add(E&) = 0;
	virtual void remove(E) = 0;
	virtual std::vector<E> all() = 0;
};