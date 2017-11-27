/*
 * redis_conn_pool.cc
 * Author: wmz
 */

#include "redis_c.hpp"

CRedisConnPool* CRedisConnPool::redisConnPool_ = NULL;
boost::mutex CRedisConnPool::instance_mutex_;

CRedisConnPool::CRedisConnPool()
{
}

CRedisConnPool::~CRedisConnPool()
{
	Destroy();
}

CRedisConnPool* CRedisConnPool::GetInstance()
{
	if (NULL == redisConnPool_)
	{
		boost::unique_lock<boost::mutex> lock(instance_mutex_);
		if (NULL == redisConnPool_)
		{
			redisConnPool_ = new CRedisConnPool;
		}
	}

	return redisConnPool_;
}

bool CRedisConnPool::Init(const RedisConnInfo& redisConnInfo)
{
	redisConnInfo_ = redisConnInfo;
	for (int i = 0; i < redisConnInfo_.max_conn_num; ++i)
	{
		redisContext* conn = CreateNewRedisContext();
		if (NULL == conn)
		{
//			LOG4CXX_ERROR(g_logger, "CRedisConnPool::Init error. num = " << i);
			return false;
		}

		queue_redisContext_.push_back(conn);
	}

	return true;
}

void CRedisConnPool::Destroy()
{
	std::deque<redisContext*>::iterator iter;
	for(iter=queue_redisContext_.begin(); iter!= queue_redisContext_.end(); ++iter)
	{
		SafeRedisFree(*iter);
	}
}

redisContext* CRedisConnPool::CreateNewRedisContext()
{
	struct timeval timeout =
	{ 1, 500000 }; // 1.5 seconds
	redisContext* conn = redisConnectWithTimeout(redisConnInfo_.ip.c_str(), redisConnInfo_.port, timeout);
	if (conn != NULL && conn->err)
	{
//		LOG4CXX_ERROR(g_logger, "CRedisConnPool::CreateNewRedisContext failed. error = " << conn->errstr);
		return NULL;
	}

	return conn;
}

redisContext* CRedisConnPool::GetRedisContext()
{
	boost::unique_lock<boost::mutex> lock(instance_mutex_);
	redisContext* conn = NULL;
	if (!queue_redisContext_.empty())
	{
		conn = queue_redisContext_.front();
		queue_redisContext_.pop_front();
	}
	else
	{
		conn = CreateNewRedisContext();
		assert(conn != NULL);
	}

	return conn;
}

void CRedisConnPool::ReleaseRedisContext(redisContext* conn)
{
	boost::unique_lock<boost::mutex> lock(instance_mutex_);
	if (conn)
	{
		/* 防止误操作导致队列有相同连接 */
		bool found = false;
		for (unsigned int i = 0; i < queue_redisContext_.size(); ++i)
		{
			if (queue_redisContext_.at(i) == conn)
			{
				found = true;
				break;
			}
		}

		if (!found)
		{
			queue_redisContext_.push_back(conn);
		}
	}
}
