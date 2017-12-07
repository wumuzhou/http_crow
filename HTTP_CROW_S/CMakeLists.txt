cmake_minimum_required(VERSION 3.9)
project(http_server)

set(CMAKE_CXX_STANDARD 11)
add_definitions(-DCROW_ENABLE_SSL)
add_definitions(-DBOOST_LOG_DYN_LINK)

include_directories(/usr/local/include)
link_directories(/usr/local/lib)

set(SOURCE_FILES
        logging.hpp
        http_server.cpp
        configurefile.hpp
        json_work.cpp
        json_work.hpp
        redis_c.cpp
        redis_c.hpp
        sql_work.cpp
        sql_work.hpp
        utils.hpp
        work_run.hpp
        message.hpp
)

add_executable(http_server ${SOURCE_FILES})

target_link_libraries(http_server boost_regex)
target_link_libraries(http_server boost_filesystem)
target_link_libraries(http_server boost_system)
target_link_libraries(http_server boost_locale)
target_link_libraries(http_server boost_thread)
target_link_libraries(http_server boost_log_setup)
target_link_libraries(http_server boost_log)
target_link_libraries(http_server pthread)
target_link_libraries(http_server ssl)
target_link_libraries(http_server crypto)
target_link_libraries(http_server dl)
target_link_libraries(http_server zdb)
target_link_libraries(http_server hiredis)
#target_link_libraries(http_server ssl)