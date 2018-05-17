#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// https://github.com/edenhill/librdkafka/blob/master/src-cpp/rdkafkacpp.h
#include <librdkafka/rdkafkacpp.h>
class MockRdKafkaKafkaConsumer : public RdKafka::KafkaConsumer
{
public:
	MOCK_METHOD1(assignment, RdKafka::ErrorCode(std::vector<RdKafka::TopicPartition*>&));
	MOCK_METHOD1(subscription, RdKafka::ErrorCode(std::vector<std::string>&));
	MOCK_METHOD1(subscribe, RdKafka::ErrorCode(const std::vector<std::string>&));
	MOCK_METHOD0(unsubscribe, RdKafka::ErrorCode());
	MOCK_METHOD1(assign, RdKafka::ErrorCode(const std::vector<RdKafka::TopicPartition*>&));
	MOCK_METHOD0(unassign, RdKafka::ErrorCode());
	MOCK_METHOD1(consume, RdKafka::Message*(int));
	MOCK_METHOD0(commitSync, RdKafka::ErrorCode());
	MOCK_METHOD0(commitAsync, RdKafka::ErrorCode());
	MOCK_METHOD1(commitSync, RdKafka::ErrorCode(RdKafka::Message*));
	MOCK_METHOD1(commitAsync, RdKafka::ErrorCode(RdKafka::Message*));
	MOCK_METHOD1(commitSync, RdKafka::ErrorCode(std::vector<RdKafka::TopicPartition*>&));
	MOCK_METHOD1(commitAsync, RdKafka::ErrorCode(const std::vector<RdKafka::TopicPartition*>&));
	MOCK_METHOD2(committed, RdKafka::ErrorCode(std::vector<RdKafka::TopicPartition*>&, int));
	MOCK_METHOD1(position, RdKafka::ErrorCode(std::vector<RdKafka::TopicPartition*>&));
	MOCK_METHOD0(close, RdKafka::ErrorCode());
	MOCK_METHOD2(seek, RdKafka::ErrorCode(const RdKafka::TopicPartition&, int));
	MOCK_METHOD1(offset_store, RdKafka::ErrorCode(std::vector<RdKafka::TopicPartition*>&));
};

