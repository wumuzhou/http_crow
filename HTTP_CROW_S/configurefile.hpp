 // Author: wmz
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>

typedef struct sqlConnInfo_
{
	int max_conn_num;
	int pool_size;
	std::string ip;
	std::string port;
	std::string user_name;
	std::string password;
	std::string db1;
} SqlConnInfo;

int configure_sql_info(SqlConnInfo& sqlConnInfo) {
	try {
		boost::property_tree::ptree pt;
		boost::property_tree::ini_parser::read_ini("http_conf.ini", pt);
		sqlConnInfo.max_conn_num = pt.get<int>("SQL_IP_MASTER.max_conn_num");
		sqlConnInfo.pool_size = pt.get<int>("SQL_IP_MASTER.pool_size");
		sqlConnInfo.ip = pt.get< std::string>("SQL_IP_MASTER.ip");
		sqlConnInfo.port = pt.get< std::string>("SQL_IP_MASTER.port");
		sqlConnInfo.user_name = pt.get< std::string>("SQL_IP_MASTER.username");
		sqlConnInfo.password = pt.get< std::string>("SQL_IP_MASTER.password");
		sqlConnInfo.db1 = pt.get< std::string>("SQL_IP_MASTER.db1");
	} catch (...) {
		throw;
	}
	return 0;
}

int configure_http_port(int& port) {
	try {
		boost::property_tree::ptree pt;
		boost::property_tree::ini_parser::read_ini("http_conf.ini", pt);
		port= pt.get<int>("HTTP_PORT.port_master");
	} catch (...) {
		throw ;
	}
	return 0;
}
