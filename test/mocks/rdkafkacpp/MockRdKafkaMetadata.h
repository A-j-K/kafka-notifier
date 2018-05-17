#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// https://github.com/edenhill/librdkafka/blob/master/src-cpp/rdkafkacpp.h
#include <librdkafka/rdkafkacpp.h>
class MockRdKafkaMetadata : public RdKafka::Metadata
{
public:
	MOCK_CONST_METHOD0(brokers, const RdKafka::Metadata::BrokerMetadataVector*());
	MOCK_CONST_METHOD0(topics, const RdKafka::Metadata::TopicMetadataVector*());
	MOCK_CONST_METHOD0(orig_broker_id, int32_t());
	MOCK_CONST_METHOD0(orig_broker_name, const std::string());
};

