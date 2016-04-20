#pragma once
#include "datetime.h"
#include "dipendente.h"
#include <string>

using namespace std;
using namespace date;

class Pianificazione
{
public:
	virtual datetime get_inizio() const = 0;
	virtual datetime get_fine() const = 0;
	virtual DipendenteId get_id_dipendente() const = 0;
	virtual void pianifica(DipendenteId, datetime, datetime) = 0;
};

class Assenza : public Pianificazione
{
public:
	Assenza(string motivazione);

	string get_motivazione() const { return motivazione_; }
	datetime get_inizio() const override { return inizio_; }
	datetime get_fine() const override { return fine_; }
	virtual DipendenteId get_id_dipendente() const { return dipId_; }
	
	void pianifica(DipendenteId id_dipendente, datetime inizio, datetime fine) override;
private:
	datetime inizio_, fine_;
	DipendenteId dipId_;
	string motivazione_;
};

class Presenza : public Pianificazione
{
public:
	Presenza(string reparto);

	string get_reparto() const { return reparto_; }
	datetime get_inizio() const override { return inizio_; }
	datetime get_fine() const override { return fine_; }
	virtual DipendenteId get_id_dipendente() const { return dipId_; }

	void pianifica(DipendenteId id_dipendente, datetime inizio, datetime fine) override;
private:
	datetime inizio_, fine_;
	DipendenteId dipId_;
	string reparto_;
};