 // Author: wmz
#include "crow.h"
#include "sql_work.hpp"
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <iostream>
#include "json_work.hpp"
#include "logging.hpp"
#include "boost/algorithm/string.hpp"

using namespace rapidjson;


void work_http1(crow::SimpleApp &app) {

    crow::mustache::set_base(".");

    CROW_ROUTE(app, "/")
            .name("hello")
                    ([] {
                        LOG_TRACE << "hello world is work";
                        return "Hello World!";
                    });

    CROW_ROUTE(app, "/chat")
    ([]{
        crow::mustache::context ctx;
        LOG_TRACE << "chat is work";
        std::string html_str = crow::mustache::load("example_chat.html").render();
        boost::algorithm::replace_all(html_str, "${send_name}", "send_cuibei");
        return html_str;
    });

    CROW_ROUTE(app, "/params_test").methods("GET"_method)
            ([](const crow::request &req) {
                if (req.url_params.get("phone") != nullptr) {
                    std::ostringstream os;
                    CSqlOpt csql ;
                    aiwei::CJsonOpt c_json;
                    int status ;
                    std::string phone = req.url_params.get("phone");
                    int result = csql.IsUserActivateFromDB(phone, status);
                    c_json.join_string_IsUserActivate(os, status);
                    return crow::response(os.str());
                }
            });


}
