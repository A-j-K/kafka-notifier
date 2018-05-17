#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// https://github.com/edenhill/librdkafka/blob/master/src-cpp/rdkafkacpp.h
#include <librdkafka/rdkafkacpp.h>
class MockRdKafkaConsumer : public RdKafka::Consumer
{
public:
	MOCK_METHOD4(start, RdKafka::ErrorCode(RdKafka::Topic*,int32_t,int64_t,RdKafka::Queue*));
	MOCK_METHOD2(stop, RdKafka::ErrorCode(RdKafka::Topic*,int32_t));
	MOCK_METHOD4(seek, RdKafka::ErrorCode(RdKafka::Topic*,int32_t,int64_t,RdKafka::Queue*));
	MOCK_METHOD3(consume, RdKafka::Message*(RdKafka::Topic*,int32_t,int));
	MOCK_METHOD2(consume, RdKafka::Message*(RdKafka::Queue*,int));
	MOCK_METHOD5(consume_callback, int(RdKafka::Topic*,int32_t,int,RdKafka::ConsumeCb*,void*));
	MOCK_METHOD4(consume_callback, int(RdKafka::Queue*,int,RdKafka::ConsumeCb*,void*));
};

