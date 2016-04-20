#pragma once
#include "repository.h"
#include "dipendente.h"
#include <vector>

using namespace std;
class DipendenteRepository : public Repository<Dipendente>
{
public:
	DipendenteRepository();
	~DipendenteRepository();

	virtual Dipendente get(int);
	virtual void add(Dipendente& d);
	virtual void remove(Dipendente d);
	virtual vector<Dipendente> all();
private:
	vector<Dipendente> db;
};