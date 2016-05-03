#pragma once
#include "repository.h"
#include "pianificazione.h"
#include <vector>
#include <mysql.h>

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
	virtual std::vector<Presenza> getByDate(date::datetime, date::datetime=date::datetime(31,12,2099));
	virtual void store(Presenza&);
private:
	date::datetime convertDateFromDb(std::string dateDb);
	vector<Presenza> db;
	MYSQL *mysql;
};
