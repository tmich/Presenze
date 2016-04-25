#include "stdafx.h"
#include "repositorypresenze.h"

Presenza RepositoryPresenze::add(DipendenteId idDipendente, date::datetime dataInizio, date::datetime dataFine, string reparto)
{
	Presenza p(reparto);
	p.pianifica(idDipendente, dataInizio, dataFine);
	p.set_id(35);
	return p;
}

void RepositoryPresenze::remove(Presenza)
{
}
