#include "stdafx.h"
#include "repositorydipendente.h"

RepositoryDipendente::RepositoryDipendente()
{
	db = {
		Dipendente("Mario", "Rossi"),
		Dipendente("Carlo", "Bianchi"),
		Dipendente("Gino", "Verdi"),
		Dipendente("Eschilo", "Auritosfrate"),
		Dipendente("Teomondo", "Scrofalo")
	};
}

RepositoryDipendente::~RepositoryDipendente()
{
}

Dipendente RepositoryDipendente::get(int)
{
	return Dipendente("mario", "rossi");
}

Dipendente RepositoryDipendente::add(string nome, string cognome)
{
	Dipendente d(nome, cognome);
	d.set_id(18);
	db.push_back(d);
	return d;
}

void RepositoryDipendente::remove(Dipendente d)
{
}

void RepositoryDipendente::store(Dipendente& dip)
{
	db.push_back(dip);
}

vector<Dipendente> RepositoryDipendente::all()
{
	return db;
}
