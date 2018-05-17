#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// https://github.com/edenhill/librdkafka/blob/master/src-cpp/rdkafkacpp.h
#include <librdkafka/rdkafkacpp.h>
class MockRdKafkaConsumeCb : public RdKafka::ConsumeCb
{
public:
	MOCK_METHOD2(consume_cb, void(RdKafka::Message&,void*));
};

