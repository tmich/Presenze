#include "stdafx.h"
#include <sstream>
#include "repositorydipendente.h"
#include "my_conn.h"

RepositoryDipendente::RepositoryDipendente()
{
	/*db = {
		Dipendente("Mario", "Rossi"),
		Dipendente("Carlo", "Bianchi"),
		Dipendente("Gino", "Verdi"),
		Dipendente("Eschilo", "Auritosfrate"),
		Dipendente("Teomondo", "Scrofalo")
	};*/
}

RepositoryDipendente::~RepositoryDipendente()
{
}

Dipendente RepositoryDipendente::get(int id)
{
	mysql = mysql_init(nullptr);
	MyConn cnninfo;

	if (mysql_real_connect(mysql, cnninfo.Host.c_str(), cnninfo.User.c_str(), cnninfo.Pass.c_str(), cnninfo.Db.c_str(), cnninfo.Port, cnninfo.Socket.c_str(), cnninfo.Flags) == nullptr)
	{
		throw std::string("Exception in mysql_real_connect: ") + std::string(mysql_error(mysql));
	}

	std::ostringstream sql;
	sql << "SELECT id, nome, cognome FROM dipendenti WHERE id = " << id << " LIMIT 1;";
	
	if (mysql_query(mysql, sql.str().c_str()))
	{
		throw std::string("Exception in mysql_query: ") + std::string(mysql_error(mysql));
	}

	MYSQL_RES *result = mysql_store_result(mysql);

	if (result == nullptr)
	{
		throw std::string("Exception in mysql_store_result: ") + std::string(mysql_error(mysql));
	}

	int num_fields = mysql_num_fields(result);

	MYSQL_ROW row;

	row = mysql_fetch_row(result);

	std::string nome{ "" }, cognome{ "" };

	if (row != nullptr)
	{
		nome = row[1];
		cognome = row[2];
	}

	mysql_free_result(result);
	mysql_close(mysql);
	
	Dipendente dip{ nome, cognome };
	dip.set_id(id);

	return dip;
}

Dipendente RepositoryDipendente::add(string nome, string cognome)
{
	Dipendente d(nome, cognome);
	d.set_id(18);
	db.push_back(d);
	return d;
}

void RepositoryDipendente::remove(Dipendente d)
{
}

void RepositoryDipendente::store(Dipendente& dip)
{
	db.push_back(dip);
}

vector<Dipendente> RepositoryDipendente::all()
{
	vector<Dipendente> results;
	mysql = mysql_init(nullptr);
	MyConn cnninfo;

	if (mysql_real_connect(mysql, cnninfo.Host.c_str(), cnninfo.User.c_str(), cnninfo.Pass.c_str(), cnninfo.Db.c_str(), cnninfo.Port, cnninfo.Socket.c_str(), cnninfo.Flags) == nullptr)
	{
		throw std::string("Exception in mysql_real_connect: ") + std::string(mysql_error(mysql));
	}

	std::ostringstream sql;
	sql << "SELECT id, nome, cognome, indirizzo FROM dipendenti;";

	if (mysql_query(mysql, sql.str().c_str()))
	{
		throw std::string("Exception in mysql_query: ") + std::string(mysql_error(mysql));
	}

	MYSQL_RES *result = mysql_store_result(mysql);

	if (result == nullptr)
	{
		throw std::string("Exception in mysql_store_result: ") + std::string(mysql_error(mysql));
	}	

	MYSQL_ROW row;

	while ((row = mysql_fetch_row(result)))
	{
		Dipendente dip(row[1], row[2]);
		dip.set_id(atoi(row[0]));
		dip.set_indirizzo(row[3]);
		results.push_back(dip);
	}

	mysql_free_result(result);
	mysql_close(mysql);

	return results;
}
