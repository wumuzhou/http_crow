 // Author: wmz
#include "json_work.hpp"

#include <boost/timer.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/barrier.hpp>

using namespace http_crow;
using namespace rapidjson;

void CJsonOpt::join_string_IsUserActivate(std::ostringstream& os, int& status)
{
    StringBuffer s;
    Writer<StringBuffer> writer(s);
    writer.StartObject();               // Between StartObject()/EndObject(),
    writer.Key("status");                // output a key,
    writer.Int(status);
    writer.EndObject();
    os << s.GetString();
//    boost::this_thread::sleep(boost::posix_time::milliseconds( 1000*1000 ) );
    LOG_TRACE << "this is a join_string_IsUserActivate";

}

