#include "stdafx.h"
#include "pianificazione.h"
#include <exception>

Assenza::Assenza(string motivazione)
	: motivazione_{ motivazione }, dipId_{0}
{
}

void Assenza::pianifica(DipendenteId id_dipendente, datetime inizio, datetime fine)
{
	if (inizio > fine)
	{
		throw invalid_argument("inizio successivo alla fine");
	}

	dipId_ = id_dipendente;
	inizio_ = inizio;
	fine_ = fine;
}

Presenza::Presenza(string reparto)
	: reparto_{ reparto }, dipId_{ 0 }
{
}

void Presenza::pianifica(DipendenteId id_dipendente, datetime inizio, datetime fine)
{
	if (inizio > fine)
	{
		throw invalid_argument("inizio successivo alla fine");
	}

	dipId_ = id_dipendente;
	inizio_ = inizio;
	fine_ = fine;
}