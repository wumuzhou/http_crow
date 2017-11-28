CXXFLAGS =	-std=c++11 -O2 -g -Wall -fmessage-length=0  -D CROW_ENABLE_SSL -D BOOST_LOG_DYN_LINK 

OBJS =	http_server.o redis_c.o sql_work.o json_work.o

LIBS =-lboost_system -lboost_thread -lboost_regex -lboost_system -lhiredis -lboost_regex\
	  -lboost_log_setup -lboost_log -lzdb \
	  -lpthread -lcrypto -lssl -ldl -lhiredis -Wl,-rpath,/usr/local/lib

TARGET =	http_server

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
