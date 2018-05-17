#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// https://github.com/edenhill/librdkafka/blob/master/src-cpp/rdkafkacpp.h
#include <librdkafka/rdkafkacpp.h>
class MockRdKafkaTopicMetadata : public RdKafka::TopicMetadata
{
public:
	MOCK_CONST_METHOD0(topic, const std::string());
	MOCK_CONST_METHOD0(partitions, const RdKafka::TopicMetadata::PartitionMetadataVector*());
	MOCK_CONST_METHOD0(err, RdKafka::ErrorCode());
};

