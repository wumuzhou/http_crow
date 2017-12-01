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

#define SQL_GET_STRING(result, parm1, field) \
if(ResultSet_getStringByName(result, field)) \
{ \
	parm1 = ResultSet_getStringByName(result, field); \
} \
else{ \
	parm1 = ""; \
} \


#define SQL_GET_INT(result, parm1, field) \
if(ResultSet_getIntByName(result, field)) \
{ \
	parm1 = ResultSet_getIntByName(result, field); \
} \
else{ \
	parm1 = 0; \
} \


class CSqlOpt
{
public:
	CSqlOpt();
	virtual ~CSqlOpt();

public:
	int IsUserActivateFromDB(const std::string& account_name, int& activate_status);

};

#endif /* SQL_OPT_H_ */
