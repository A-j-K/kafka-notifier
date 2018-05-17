
#include <sstream>
#include <string>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <stdexcept>
#include <exception>

#include "utils.hpp"
#include "kafka_consume_cb.hpp"

#include "mocks/MockCurler.hpp"
#include "mocks/rdkafkacpp/MockRdKafkaTopic.h"
#include "mocks/rdkafkacpp/MockRdKafkaMessage.h"
#include "mocks/rdkafkacpp/MockRdKafkaConsumeCb.h"

using ::testing::_;
using ::testing::StrEq;
using ::testing::Return; 
using ::testing::AtLeast;
using ::testing::Matcher;
using ::testing::NiceMock;
using ::testing::ReturnRef; 

// Fixture
class test_kafka_consume_cb : public ::testing::Test
{
public:
	std::stringstream *_poss;
	KafkaConsumeCallback *_pKafkaConsumeCallback;
	MockRdKafkaMessage *_pMessage;
	MockRdKafkaTopic   *_pTopic;
	MockCurler *_pCurler;
	virtual void SetUp() {
		_poss = new std::stringstream;
		_pTopic = new NiceMock<MockRdKafkaTopic>;
		_pCurler = new NiceMock<MockCurler>;
		_pMessage = new NiceMock<MockRdKafkaMessage>;
		_pKafkaConsumeCallback = new KafkaConsumeCallback;
		_pKafkaConsumeCallback->setOutputStream(_poss);
	}
	virtual void TearDown() {
		delete _pKafkaConsumeCallback;
		delete _pMessage;
		delete _pTopic;
		delete _pCurler;
		delete _poss;
	}
};

TEST_F(test_kafka_consume_cb, test_send_no_errors)
{
	const char *payload = "TestPayload";
	int  length = sizeof("TestPayload")-1;
	std::string actual_key("TestKey");
	const std::string actual_topic("TestTopic");
	CurlerRval::ShPtr actual_curler_rval(new CurlerRval);
	actual_curler_rval->_result = CURLE_OK;

	EXPECT_CALL(*_pTopic, name())
		.WillOnce(Return(actual_topic));
	EXPECT_CALL(*_pMessage, key())
		.WillOnce(Return((const std::string*)&actual_key));
	EXPECT_CALL(*_pMessage, topic())
		.WillOnce(Return(_pTopic));
	EXPECT_CALL(*_pMessage, partition())
		.WillOnce(Return(5));
	EXPECT_CALL(*_pMessage, offset())
		.WillOnce(Return(2000));
	EXPECT_CALL(*_pMessage, payload())
		.WillOnce(Return((char*)payload));
	EXPECT_CALL(*_pMessage, len())
		.WillOnce(Return(length));
	EXPECT_CALL(*_pCurler, send(_,_,_))
		.WillOnce(Return(actual_curler_rval));

	_pKafkaConsumeCallback->send(_pMessage, _pCurler);
}

TEST_F(test_kafka_consume_cb, test_send_bad_curle_ok_causes_exception)
{
	const char *payload = "TestPayload";
	int  length = sizeof("TestPayload")-1;
	std::string actual_key("TestKey");
	const std::string actual_topic("TestTopic");
	CurlerRval::ShPtr actual_curler_rval(new CurlerRval);

	// Anything other than CURLE_OK...
	actual_curler_rval->_result = CURLE_COULDNT_CONNECT;

	EXPECT_CALL(*_pTopic, name())
		.WillOnce(Return(actual_topic));
	EXPECT_CALL(*_pMessage, key())
		.WillOnce(Return((const std::string*)&actual_key));
	EXPECT_CALL(*_pMessage, topic())
		.WillOnce(Return(_pTopic));
	EXPECT_CALL(*_pMessage, partition())
		.WillOnce(Return(5));
	EXPECT_CALL(*_pMessage, offset())
		.WillOnce(Return(2000));
	EXPECT_CALL(*_pMessage, payload())
		.WillOnce(Return((char*)payload));
	EXPECT_CALL(*_pMessage, len())
		.WillOnce(Return(length));
	EXPECT_CALL(*_pCurler, send(_,_,_))
		.WillOnce(Return(actual_curler_rval));

	try {
		_pKafkaConsumeCallback->send(_pMessage, _pCurler);
		FAIL() << "Expected exception not thrown";
	}
	catch(std::runtime_error *e) {
		std::string actual(e->what());
		ASSERT_EQ("Need to handle this error", actual);
	}
	catch(...) {
		FAIL() << "Unexpected exception";
	}
}


