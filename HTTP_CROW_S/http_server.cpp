 // Author: wmz
#include "utils.hpp"
#include <iostream>
#include <sstream>
#include "configurefile.hpp"
#include "work_run.hpp"
#include "logging.hpp"
#include "sql_work.hpp"


#define DB1 "account"
using namespace std;


ConnectionPool_T pool_sql;

int init_log_conf() {
    std::ifstream settings("settings.txt");
    if (!settings.is_open()) {
        BOOST_LOG_SEV(logger::get(), 5) << "Could not open settings.txt file";
        return 1;
    }
    // Read the settings and initialize logging library
    logging::init_from_stream(settings);

    // Add some attributes
    logging::add_common_attributes();
    return 0;
}

void sql_init(SqlConnInfo& sqlConnInfo) {
    // setting sql
    configure_sql_info(sqlConnInfo);
    LOG_IMPORTANT << "sqlConnInfo.max_conn_num==" << sqlConnInfo.max_conn_num;
    LOG_IMPORTANT << "sqlConnInfo.ip==" << sqlConnInfo.ip;
    LOG_IMPORTANT << "sqlConnInfo.port==" << sqlConnInfo.port;
    LOG_IMPORTANT << "sqlConnInfo.user_name==" << sqlConnInfo.user_name;
    LOG_IMPORTANT << "sqlConnInfo.password==" << sqlConnInfo.password;
    // init sql
    std::string mysql_url_db1 =
            "mysql://" + sqlConnInfo.ip + "/" + DB1 + "?user=" + sqlConnInfo.user_name + "&password=" +
            sqlConnInfo.password;
    LOG_IMPORTANT << "mysql_url_db1==   " << mysql_url_db1;
    URL_T url = URL_new(mysql_url_db1.c_str());

    if (url == NULL) {
        printf("URL parse ERROR!\n");
    }
    pool_sql = ConnectionPool_new(url);
    //init num of pool connect
    ConnectionPool_setInitialConnections(pool_sql, 5);
    ConnectionPool_start(pool_sql);

}


int main() {
    crow::SimpleApp app;
    if (init_log_conf() == 1) exit(0);
    int PORT;
    SqlConnInfo sqlConnInfo;
    //1. start config
    configure_http_port(PORT);
    LOG_IMPORTANT << "SERVER PORT=== " << PORT;

    sql_init(sqlConnInfo);

    //2.  running in daemon
    if (daemon(1, 0) == -1) {
        LOG_ERROR << "this is error in daemon";
        return 0;
    }

    //3. work start
    work_http1(app);
//	app.loglevel(crow::LogLevel::DEBUG);
    app.loglevel(crow::LogLevel::INFO);
    app.port(PORT).multithreaded().run();

}
