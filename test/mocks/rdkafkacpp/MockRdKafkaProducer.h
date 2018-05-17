#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// https://github.com/edenhill/librdkafka/blob/master/src-cpp/rdkafkacpp.h
#include <librdkafka/rdkafkacpp.h>
class MockRdKafkaProducer : public RdKafka::Producer
{
public:
	MOCK_METHOD7(produce, RdKafka::ErrorCode(RdKafka::Topic*,int32_t,int,void*,size_t,std::string*,void*));
	MOCK_METHOD8(produce, RdKafka::ErrorCode(RdKafka::Topic*,int32_t,int,void*,size_t,const void*,size_t,void*));
	MOCK_METHOD9(produce, RdKafka::ErrorCode(const std::string,int32_t,int,void*,size_t,const void*,size_t,int64_t,void*));
	MOCK_METHOD5(produce, RdKafka::ErrorCode(RdKafka::Topic*,int32_t,const std::vector<char>,const std::vector<char>,void*));
	MOCK_METHOD1(flush, RdKafka::ErrorCode(int));
};

