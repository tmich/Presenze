#include "stdafx.h"
#include "dipendenterepository.h"

DipendenteRepository::DipendenteRepository()
{
}

DipendenteRepository::~DipendenteRepository()
{
}

Dipendente DipendenteRepository::get(int)
{
	return Dipendente("mario", "rossi");
}

void DipendenteRepository::add(Dipendente& d)
{
	d.set_id(18);
	db.push_back(d);
}

void DipendenteRepository::remove(Dipendente d)
{
}

vector<Dipendente> DipendenteRepository::all()
{
	return db;
}
