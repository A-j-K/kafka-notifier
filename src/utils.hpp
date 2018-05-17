#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>
#include <sstream>
#include <librdkafka/rdkafkacpp.h>

#ifdef BUILD_TESTS
#define PROTECTED public
#else
#define PROTECTED public
#endif

class Utils
{
public:
	typedef std::vector<std::string> StringVector;
	typedef std::map<std::string, std::string> KeyValue;

	typedef std::shared_ptr<RdKafka::Conf> KafkaConfShPtr;
	typedef std::shared_ptr<RdKafka::KafkaConsumer> KafkaConsumerShPtr;
};


// http://stackoverview.blogspot.co.uk/2011/04/create-string-on-fly-just-in-one-line.html
struct stringbuilder
{
   std::stringstream ss;
   template<typename T>
   stringbuilder & operator << (const T &data)
   {
        ss << data;
        return *this;
   }
   operator std::string() { return ss.str(); }
};

