/*
 * sql_opt.h
 *
 * Author: wmz
 */

#ifndef SQL_OPT_H_
#define SQL_OPT_H_

#include <string>
#include <map>
#include "logging.hpp"
#include<zdb/zdb.h>
#include<zdb/Exception.h>
#include<zdb/Connection.h>
#include<zdb/URL.h>
#include <iostream>



class CSqlOpt
{
public:
	CSqlOpt();
	virtual ~CSqlOpt();

public:
	int IsUserActivateFromDB(const std::string& account_name, int& activate_status);

};

#endif /* SQL_OPT_H_ */
