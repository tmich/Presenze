#include "stdafx.h"
#include "repositorypresenze.h"
#include "my_conn.h"
#include <sstream>

RepositoryPresenze::RepositoryPresenze()
{
}

RepositoryPresenze::~RepositoryPresenze()
{
}

Presenza RepositoryPresenze::get(int id)
{
	mysql = mysql_init(nullptr);
	MyConn cnninfo;

	if (mysql_real_connect(mysql, cnninfo.Host.c_str(), cnninfo.User.c_str(), cnninfo.Pass.c_str(), cnninfo.Db.c_str(), cnninfo.Port, cnninfo.Socket.c_str(), cnninfo.Flags) == nullptr)
	{
		throw std::string("Exception in mysql_real_connect: ") + std::string(mysql_error(mysql));
	}

	std::ostringstream sql;
	sql << "SELECT id, dipendente_id, DATE_FORMAT(data_inizio, '%Y%m%d %H%i%S'), DATE_FORMAT(data_fine, '%Y%m%d %H%i%S'), reparto FROM presenze WHERE id = " << id << ";";

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

	row = mysql_fetch_row(result);

	int id_ = 0;
	int dipendente_id;
	std::string reparto;
	datetime data_inizio, data_fine;

	if (row != nullptr)
	{
		id_ = atoi(row[0]);
		dipendente_id = atoi(row[1]);
		data_inizio = date::parse_iso8601(row[2]);
		data_fine = date::parse_iso8601(row[3]);
	}

	mysql_free_result(result);
	mysql_close(mysql);

	if (id_ > 0)
	{
		return Presenza(id_, dipendente_id, data_inizio, data_fine, reparto);

	}
	return nullptr;
}

Presenza RepositoryPresenze::add(DipendenteId idDipendente, date::datetime dataInizio, date::datetime dataFine, string reparto)
{
	Presenza p(reparto);
	p.pianifica(idDipendente, dataInizio, dataFine);

	mysql = mysql_init(nullptr);
	MyConn cnninfo;

	if (mysql_real_connect(mysql, cnninfo.Host.c_str(), cnninfo.User.c_str(), cnninfo.Pass.c_str(), cnninfo.Db.c_str(), cnninfo.Port, cnninfo.Socket.c_str(), cnninfo.Flags) == nullptr)
	{
		throw std::string("Exception in mysql_real_connect: ") + std::string(mysql_error(mysql));
	}

	std::ostringstream sql;
	sql << "INSERT INTO presenze (dipendente_id, data_inizio, data_fine, reparto) values ("
		<< p.get_id_dipendente() << ", str_to_date('" << p.get_inizio().to_string() << "', '%d/%m/%Y %H:%i:%S')"
		<< ", str_to_date('" << p.get_fine().to_string() << "', '%d/%m/%Y %H:%i:%S'), '" << p.get_reparto() << "');";

	if (mysql_query(mysql, sql.str().c_str()))
	{
		throw std::string("Exception in mysql_query: ") + std::string(mysql_error(mysql));
	}
	p.set_id(mysql_insert_id(mysql));
	mysql_commit(mysql);
	mysql_close(mysql);
	return p;
	//db.push_back(p);
	//db[db.size() - 1].set_id(db.size());
	//return db[db.size() - 1];
}

void RepositoryPresenze::remove(Presenza)
{
}

std::vector<Presenza> RepositoryPresenze::all()
{
	return db;
}

std::vector<Presenza> RepositoryPresenze::getByDate(date::datetime data1, date::datetime data2)
{
	std::vector<Presenza> presenze;
	mysql = mysql_init(nullptr);
	MyConn cnninfo;

	if (mysql_real_connect(mysql, cnninfo.Host.c_str(), cnninfo.User.c_str(), cnninfo.Pass.c_str(), cnninfo.Db.c_str(), cnninfo.Port, cnninfo.Socket.c_str(), cnninfo.Flags) == nullptr)
	{
		throw std::string("Exception in mysql_real_connect: ") + std::string(mysql_error(mysql));
	}

	std::ostringstream sql;
	sql << "SELECT id, dipendente_id, data_inizio, data_fine, reparto FROM presenze WHERE data_inizio >= str_to_date('" << 
		data1.to_date_string() << " 00:00:00','%d/%m/%Y %H:%i:%S') and data_inizio <= str_to_date('" << 
		data2.to_date_string() << " 23:59:59','%d/%m/%Y %H:%i:%S');";

	if (mysql_query(mysql, sql.str().c_str()))
	{
		throw std::string("Exception in mysql_query: ") + std::string(mysql_error(mysql));
	}

	MYSQL_RES *result = mysql_store_result(mysql);

	if (result == nullptr)
	{
		throw std::string("Exception in mysql_store_result: ") + std::string(mysql_error(mysql));
	}

	while (MYSQL_ROW row = mysql_fetch_row(result))
	{
		int id = atoi(row[0]);
		int dipId = atoi(row[1]);
		date::datetime d_in(convertDateFromDb(row[2]));
		date::datetime d_fn(convertDateFromDb(row[3]));
		std::string reparto(row[4]);
		Presenza p(id, dipId, d_in, d_fn, reparto);
		presenze.push_back(p);
	}
	
	mysql_free_result(result);
	mysql_close(mysql);

	return presenze;
}

void RepositoryPresenze::store(Presenza& presenza)
{
	mysql = mysql_init(nullptr);
	MyConn cnninfo;

	if (mysql_real_connect(mysql, cnninfo.Host.c_str(), cnninfo.User.c_str(), cnninfo.Pass.c_str(), cnninfo.Db.c_str(), cnninfo.Port, cnninfo.Socket.c_str(), cnninfo.Flags) == nullptr)
	{
		throw std::string("Exception in mysql_real_connect: ") + std::string(mysql_error(mysql));
	}

	std::ostringstream sql;
	sql << "UPDATE presenze SET dipendente_id = " << presenza.get_id_dipendente() << ", ";
	sql << "data_inizio = str_to_date('" << presenza.get_inizio().to_string() << "','%d/%m/%Y %H:%i:%S'), ";
	sql << "data_fine = str_to_date('" << presenza.get_fine().to_string() << "','%d/%m/%Y %H:%i:%S'), ";
	sql << "reparto = '" << presenza.get_reparto() << "' ";
	sql << "where id = " << presenza.get_id();

	if (mysql_query(mysql, sql.str().c_str()))
	{
		throw std::string("Exception in mysql_query: ") + std::string(mysql_error(mysql));
	}
	
	mysql_commit(mysql);
	mysql_close(mysql);
}

date::datetime RepositoryPresenze::convertDateFromDb(std::string dateDb)
{
	int day, month, year, hour, min, sec;
	year = stoi(dateDb.substr(0, 4));
	month = stoi(dateDb.substr(5, 2));
	day = stoi(dateDb.substr(8, 2));
	hour = stoi(dateDb.substr(11, 2));
	min = stoi(dateDb.substr(14, 2));
	sec = stoi(dateDb.substr(17, 2));
	return date::datetime(day, month, year, hour, min, sec);
}
