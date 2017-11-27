/*
 * sql_opt.cc
 * Author: wmz
 */


#include "sql_work.hpp"
#include <iostream>

#define MY_SQL_ERROR -100
#define SUCCESS 1

extern ConnectionPool_T pool_sql;

CSqlOpt::CSqlOpt() {

}

CSqlOpt::~CSqlOpt() {
}

int CSqlOpt::IsUserActivateFromDB(const std::string &account_name, int &activate_status) {

    int b_ok = SUCCESS;
    Connection_T con = ConnectionPool_getConnection(pool_sql);
    TRY
    {
        PreparedStatement_T p = Connection_prepareStatement(con,
                                                            "select activate_status from user_common where phone=? ");
        PreparedStatement_setString(p, 1, account_name.c_str());
        ResultSet_T r = PreparedStatement_executeQuery(p);
        while (ResultSet_next(r)) {
            activate_status = ResultSet_getIntByName(r, "activate_status");
            LOG_TRACE << "activate_status===============================171124===========>" << activate_status;
        }
    }
    CATCH(SQLException)
    {
        LOG_TRACE << "get the exception IsUserActivateFromDB ";
    }
    FINALLY
    {
        LOG_TRACE << "enter is finally";
        Connection_close(con);
    }
    END_TRY;

    return b_ok;
}

