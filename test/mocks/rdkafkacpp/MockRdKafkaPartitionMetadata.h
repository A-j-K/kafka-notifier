#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// https://github.com/edenhill/librdkafka/blob/master/src-cpp/rdkafkacpp.h
#include <librdkafka/rdkafkacpp.h>
class MockRdKafkaPartitionMetadata : public RdKafka::PartitionMetadata
{
public:
	MOCK_CONST_METHOD0(id, int32_t());
	MOCK_CONST_METHOD0(err, RdKafka::ErrorCode());
	MOCK_CONST_METHOD0(leader, int32_t());
	MOCK_CONST_METHOD0(replicas, const std::vector<int32_t>*());
	MOCK_CONST_METHOD0(isrs, const std::vector<int32_t>*());
};

