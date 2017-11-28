/*
 * json_operate.h
 * Author: wmz
 */

#ifndef JSON_OPERATE_H_
#define JSON_OPERATE_H_

#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <iostream>
#include "logging.hpp"


namespace http_crow{
	class CJsonOpt
	{

	public:
		void join_string_IsUserActivate(std::ostringstream& os, int& status);

	};
}

#endif /* JSON_OPERATE_H_ */
