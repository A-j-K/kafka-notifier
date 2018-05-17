#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// https://github.com/edenhill/librdkafka/blob/master/src-cpp/rdkafkacpp.h
#include <librdkafka/rdkafkacpp.h>
class MockRdKafkaTopicPartition : public RdKafka::TopicPartition
{
public:
	MOCK_METHOD0(partition, int());
	MOCK_METHOD0(offset, int64_t());
	MOCK_METHOD1(set_offset, void(int64_t));
	MOCK_CONST_METHOD0(topic, const std::string&());
	MOCK_CONST_METHOD0(err, RdKafka::ErrorCode());
};

