#include "stdafx.h"
#include "serviceturni.h"

ServiceTurni::ServiceTurni()
{
}

ServiceTurni::~ServiceTurni()
{
}

Presenza ServiceTurni::PianificaTurno(Dipendente dipendente, datetime data_inizio, datetime data_fine, string reparto)
{
	Presenza presenza(reparto);
	try
	{
		presenza.pianifica(dipendente.get_id(), data_inizio, data_fine);
		// TODO: repository turni
		return presenza;
	}
	catch (const std::exception&)
	{
		return nullptr;
	}
}

Assenza ServiceTurni::PianificaAssenza(Dipendente dipendente, datetime data_inizio, datetime data_fine, string causale)
{
	Assenza assenza(causale);
	try
	{
		assenza.pianifica(dipendente.get_id(), data_inizio, data_fine);
		// TODO: repository turni
		return assenza;
	}
	catch (const std::exception&)
	{
		return nullptr;
	}
}