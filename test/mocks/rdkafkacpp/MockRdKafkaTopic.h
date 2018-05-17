#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// https://github.com/edenhill/librdkafka/blob/master/src-cpp/rdkafkacpp.h#L1242
#include <librdkafka/rdkafka.h>

// https://github.com/edenhill/librdkafka/blob/master/src-cpp/rdkafkacpp.h
#include <librdkafka/rdkafkacpp.h>

class MockRdKafkaTopic : public RdKafka::Topic
{
public:
	MOCK_CONST_METHOD0(name, const std::string());
	MOCK_CONST_METHOD1(partition_available, bool(int32_t));
	MOCK_METHOD2(offset_store, RdKafka::ErrorCode(int32_t, int64_t));
	MOCK_METHOD0(c_ptr, struct rd_kafka_topic_s*());
};

