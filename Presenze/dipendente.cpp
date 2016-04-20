#include "stdafx.h"
#include "dipendente.h"

Dipendente::Dipendente(string nome, string cognome)
	:nome_{ nome }, cognome_{ cognome }, id_{0}
{
}

Dipendente::~Dipendente()
{
}

void Dipendente::set_nome(string nome)
{
	nome_ = nome;
}

void Dipendente::set_cognome(string cognome)
{
	cognome_ = cognome;
}

void Dipendente::set_datanascita(datetime data_nascita)
{
	dnascita_ = data_nascita;
}

void Dipendente::set_indirizzo(string indirizzo)
{
	indirizzo_ = indirizzo;
}

void Dipendente::licenzia(datetime data_licenziamento)
{
	dlicenziamento_ = data_licenziamento;
}

