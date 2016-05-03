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
	virtual int get_id() const = 0;
};

class Assenza : public Pianificazione
{
public:
	Assenza(string motivazione);

	string get_motivazione() const { return motivazione_; }
	datetime get_inizio() const override { return inizio_; }
	datetime get_fine() const override { return fine_; }
	virtual DipendenteId get_id_dipendente() const { return dipId_; }
	int get_id() const override { return id_; }
	void set_id(int id) { id_ = id; }
	void pianifica(DipendenteId id_dipendente, datetime inizio, datetime fine) override;
private:
	datetime inizio_, fine_;
	DipendenteId dipId_;
	string motivazione_;
	int id_;
};

class Presenza : public Pianificazione
{
public:
	Presenza(string reparto);
	Presenza(int id, DipendenteId id_dipendente, date::datetime data_inizio, date::datetime data_fine, std::string reparto);
	string get_reparto() const { return reparto_; }
	datetime get_inizio() const override { return inizio_; }
	datetime get_fine() const override { return fine_; }
	virtual DipendenteId get_id_dipendente() const { return dipId_; }
	int get_id() const override { return id_; }
	void set_id(int id) { id_ = id; }
	void set_reparto(string reparto) { reparto_ = reparto; }
	void pianifica(DipendenteId id_dipendente, datetime inizio, datetime fine) override;
private:
	datetime inizio_, fine_;
	DipendenteId dipId_;
	string reparto_;
	int id_;
};