#pragma once
#include "repository.h"
#include "pianificazione.h"
#include <vector>

class RepositoryPresenze : public Repository<Presenza>
{
public:
	RepositoryPresenze();
	~RepositoryPresenze();

	RepositoryPresenze(const RepositoryPresenze&) = delete;
	void operator=(RepositoryPresenze) = delete;

	virtual Presenza get(int);
	virtual Presenza add(DipendenteId, date::datetime, date::datetime, string);
	virtual void remove(Presenza);
	virtual std::vector<Presenza> all();
	virtual void store(Presenza&);
private:
	vector<Presenza> db;
};
