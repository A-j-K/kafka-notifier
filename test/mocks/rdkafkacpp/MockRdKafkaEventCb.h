#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// https://github.com/edenhill/librdkafka/blob/master/src-cpp/rdkafkacpp.h
#include <librdkafka/rdkafkacpp.h>
class MockRdKafkaEventCb : public RdKafka::EventCb
{
public:
	MOCK_METHOD1(event_cb, void(RdKafka::Event&));
};

