#pragma once
#include <string>
#include "datetime.h"

using namespace std;
using namespace date;

typedef uint32_t DipendenteId;

class Dipendente
{
public:
	Dipendente(string nome, string cognome);
	~Dipendente();

	DipendenteId get_id() { return id_; }
	void set_id(DipendenteId id) { id_ = id; }

	void set_nome(string nome);
	void set_cognome(string cognome);
	void set_datanascita(datetime data_nascita);
	void set_indirizzo(string indirizzo);

	string get_nome() { return nome_; }
	string get_cognome() { return cognome_; }
	datetime get_datanascita() { return dnascita_; }
	string get_indirizzo() { return indirizzo_; }
	
	string get_nomecompleto() { return get_nome() + " " + get_cognome(); }

	void licenzia(datetime data_licenziamento);
private:
	DipendenteId id_;
	string nome_, cognome_, indirizzo_;
	datetime dnascita_, dlicenziamento_;
};

