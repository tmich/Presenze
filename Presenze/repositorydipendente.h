#pragma once
#include "repository.h"
#include "dipendente.h"
#include <mysql.h>
#include <vector>

using namespace std;
class RepositoryDipendente : public Repository<Dipendente>
{
public:
	RepositoryDipendente();
	~RepositoryDipendente();

	virtual Dipendente get(int);
	virtual Dipendente add(string nome, string cognome);
	virtual void remove(Dipendente d);
	virtual vector<Dipendente> all();
	virtual void store(Dipendente&);
private:
	vector<Dipendente> db;
	MYSQL *mysql;
};