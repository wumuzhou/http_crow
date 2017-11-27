/*
 * redis_conn_pool.h
 * Author: wmz
 */

#ifndef REDIS_CONN_POOL_H_
#define REDIS_CONN_POOL_H_

#include <deque>
#include <hiredis/hiredis.h>
#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include "logging.hpp"

typedef struct redisConnInfo_
{
	int max_conn_num;
	std::string ip;
	int port;
} RedisConnInfo;

class CRedisConnPool
{
public:

	static CRedisConnPool* GetInstance();

	bool Init(const RedisConnInfo& redisConnInfo);
	void Destroy();

	redisContext* GetRedisContext();
	void ReleaseRedisContext(redisContext* conn);

private:
	CRedisConnPool();
	virtual ~CRedisConnPool();

	redisContext* CreateNewRedisContext();

	void SafeRedisFree(redisContext *conn)
	{
		if (conn)
		{
			redisFree(conn);
			conn = NULL;
		}
	}

	static CRedisConnPool* redisConnPool_;
	static boost::mutex instance_mutex_;
	std::deque<redisContext*> queue_redisContext_;
	RedisConnInfo redisConnInfo_;
};

#endif /* REDIS_CONN_POOL_H_ */
