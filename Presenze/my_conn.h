#pragma once
#include <string>

typedef struct strMyConn
{
	// "192.168.56.1", "benson", "metallo", "turni", 3306, 0, 0
	std::string Host = "192.168.56.1";
	std::string User = "benson";
	std::string Pass = "metallo";
	std::string Db = "turni";
	int Port = 3306;
	std::string Socket = "";
	int Flags = 0;
} MyConn;