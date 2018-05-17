#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// https://github.com/edenhill/librdkafka/blob/master/src-cpp/rdkafkacpp.h
#include <librdkafka/rdkafkacpp.h>
class MockRdKafkaBrokerMetadata : public RdKafka::BrokerMetadata
{
public:
	MOCK_CONST_METHOD0(id, int32_t());
	MOCK_CONST_METHOD0(host, const std::string());
	MOCK_CONST_METHOD0(port, int());
};

