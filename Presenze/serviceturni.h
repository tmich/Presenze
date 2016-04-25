#pragma once
#include "pianificazione.h"
#include "dipendente.h"
#include "datetime.h"

using namespace date;
class ServiceTurni
{
public:
	ServiceTurni();
	~ServiceTurni();

	Presenza PianificaTurno(Dipendente, datetime, datetime, string);
	Assenza PianificaAssenza(Dipendente, datetime, datetime, string);
private:

};
