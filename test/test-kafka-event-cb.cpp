
#include <sstream>
#include <string>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <stdexcept>
#include <exception>

#include "utils.hpp"
#include "kafka_event_cb.hpp"

#include "mocks/rdkafkacpp/MockRdKafkaEvent.h"
#include "mocks/rdkafkacpp/MockRdKafkaEventCb.h"

using ::testing::_;
using ::testing::StrEq;
using ::testing::Return; 
using ::testing::AtLeast;
using ::testing::Matcher;
using ::testing::NiceMock;
using ::testing::ReturnRef; 

// Fixture
class test_kafka_event_cb : public ::testing::Test
{
public:
	std::stringstream *_poss;
	KafkaEventCallback *_pKafkaEventCallback;
	MockRdKafkaEvent *_pEvent;
	MockRdKafkaEventCb *_pEventCb;	
	virtual void SetUp() {
		_poss = new std::stringstream;
		_pEvent  = new NiceMock<MockRdKafkaEvent>;
		_pEventCb = new NiceMock<MockRdKafkaEventCb>;
		_pKafkaEventCallback = new KafkaEventCallback;
		_pKafkaEventCallback->setOutputStream(_poss);
	}
	virtual void TearDown() {
		delete _pKafkaEventCallback;
		delete _pEvent;
		delete _pEventCb;
		delete _poss;
	}
};

TEST_F(test_kafka_event_cb, test_EVENT_ERROR_and_ERR__END)
{
	RdKafka::ErrorCode errCode;
	std::string expect("ERROR:");

	EXPECT_CALL(*_pEvent, type())
		.WillOnce(Return(RdKafka::Event::EVENT_ERROR));
	EXPECT_CALL(*_pEvent, err())
		.WillRepeatedly(Return(RdKafka::ERR__END));
	EXPECT_CALL(*_pEvent, str())
		.WillOnce(Return(std::string("event error occured")));

	_pKafkaEventCallback->event_cb(*_pEvent);
	ASSERT_EQ(expect, _poss->str().substr(0, expect.size()));
}

TEST_F(test_kafka_event_cb, test_EVENT_ERROR_and_ERR__ALL_BROKERS_DOWN)
{
	RdKafka::ErrorCode errCode;
	std::string expect("ERROR:");

	EXPECT_CALL(*_pEvent, type())
		.WillOnce(Return(RdKafka::Event::EVENT_ERROR));
	EXPECT_CALL(*_pEvent, err())
		.WillRepeatedly(Return(RdKafka::ERR__ALL_BROKERS_DOWN));
	EXPECT_CALL(*_pEvent, str())
		.WillRepeatedly(Return(std::string("Where did they go?")));

	try {
		_pKafkaEventCallback->event_cb(*_pEvent);
		FAIL() << "Expected an exception";
	}
	catch(std::runtime_error *e) {
		std::string expect("Brokers are down? Where did they go?");	
		std::string actual = std::string(e->what()).substr(0, expect.size());
		ASSERT_EQ(expect, actual);
	}
	ASSERT_EQ(expect, _poss->str().substr(0, expect.size()));
}


TEST_F(test_kafka_event_cb, test_EVENT_STATS)
{
	RdKafka::ErrorCode errCode;
	std::string expect("STATS: My stats");

	EXPECT_CALL(*_pEvent, type())
		.WillOnce(Return(RdKafka::Event::EVENT_STATS));
	EXPECT_CALL(*_pEvent, str())
		.WillOnce(Return(std::string("My stats")));

	_pKafkaEventCallback->event_cb(*_pEvent);
	ASSERT_EQ(expect, _poss->str().substr(0, expect.size()));
}

TEST_F(test_kafka_event_cb, test_EVENT_LOG)
{
	RdKafka::ErrorCode errCode;
	std::string expect("LOG-6-ThisFac: ThisStr");

	EXPECT_CALL(*_pEvent, severity())
		.WillRepeatedly(Return(RdKafka::Event::EVENT_SEVERITY_INFO));
	EXPECT_CALL(*_pEvent, fac())
		.WillRepeatedly(Return(std::string("ThisFac")));
	EXPECT_CALL(*_pEvent, str())
		.WillRepeatedly(Return(std::string("ThisStr")));
	EXPECT_CALL(*_pEvent, type())
		.WillOnce(Return(RdKafka::Event::EVENT_LOG));

	_pKafkaEventCallback->event_cb(*_pEvent);
	ASSERT_EQ(expect, _poss->str().substr(0, expect.size()));
}

TEST_F(test_kafka_event_cb, test_EVENT_THROTTLE)
{
	RdKafka::ErrorCode errCode;
	std::string expect("THROTTLE: 1000ms BrokerName id 2000");

	EXPECT_CALL(*_pEvent, throttle_time())
		.WillRepeatedly(Return(1000));
	EXPECT_CALL(*_pEvent, broker_name())
		.WillRepeatedly(Return(std::string("BrokerName")));
	EXPECT_CALL(*_pEvent, broker_id())
		.WillRepeatedly(Return(2000));
	EXPECT_CALL(*_pEvent, type())
		.WillOnce(Return(RdKafka::Event::EVENT_THROTTLE));

	_pKafkaEventCallback->event_cb(*_pEvent);
	ASSERT_EQ(expect, _poss->str().substr(0, expect.size()));
}

