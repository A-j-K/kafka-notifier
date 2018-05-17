#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// https://github.com/edenhill/librdkafka/blob/master/src-cpp/rdkafkacpp.h
#include <librdkafka/rdkafkacpp.h>
class MockRdKafkaEvent : public RdKafka::Event
{
public:
	MOCK_CONST_METHOD0(type, RdKafka::Event::Type());
	MOCK_CONST_METHOD0(err, RdKafka::ErrorCode());
	MOCK_CONST_METHOD0(severity, RdKafka::Event::Severity());
	MOCK_CONST_METHOD0(fac, std::string());
	MOCK_CONST_METHOD0(str, std::string());
	MOCK_CONST_METHOD0(throttle_time, int());
	MOCK_CONST_METHOD0(broker_name, std::string());
	MOCK_CONST_METHOD0(broker_id, int());
};

