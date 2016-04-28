#include "stdafx.h"
#include "repositorypresenze.h"

RepositoryPresenze::RepositoryPresenze()
{
}

RepositoryPresenze::~RepositoryPresenze()
{
}

Presenza RepositoryPresenze::get(int id)
{
	return db[id];
}

Presenza RepositoryPresenze::add(DipendenteId idDipendente, date::datetime dataInizio, date::datetime dataFine, string reparto)
{
	Presenza p(reparto);
	p.pianifica(idDipendente, dataInizio, dataFine);
	db.push_back(p);
	db[db.size() - 1].set_id(db.size());
	return db[db.size() - 1];
}

void RepositoryPresenze::remove(Presenza)
{
}

std::vector<Presenza> RepositoryPresenze::all()
{
	return db;
}

void RepositoryPresenze::store(Presenza& presenza)
{
	db.push_back(presenza);
}
