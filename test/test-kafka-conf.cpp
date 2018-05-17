
#include <string>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <stdexcept>
#include <exception>

#include "utils.hpp"
#include "kafka_conf.hpp"

#include "mocks/MockAbstractConfig.hpp"
#include "mocks/rdkafkacpp/MockRdKafkaConf.h"

using ::testing::_;
using ::testing::StrEq;
using ::testing::Return; 
using ::testing::AtLeast;
using ::testing::Matcher;
using ::testing::NiceMock;
using ::testing::ReturnRef; 

// Fixture
class test_kafka_conf : public ::testing::Test
{
public:
	MockRdKafkaConf		*_pConf;
	MockRdKafkaConf		*_pTopic;
	MockAbstractConfig	*_pConfig;
	virtual void SetUp() {
		_pConf  = new NiceMock<MockRdKafkaConf>;
		_pTopic = new NiceMock<MockRdKafkaConf>;
		_pConfig = new NiceMock<MockAbstractConfig>;
	}
	virtual void TearDown() {
		delete _pConf;
		delete _pTopic;
		delete _pConfig;
	}
};

TEST_F(test_kafka_conf, no_options_supplied)
{
	Utils::KeyValue options;

	ON_CALL(*_pConfig, getClientOptions())
		.WillByDefault(ReturnRef(options));
	// No options, expect no calls.
	EXPECT_CALL(*_pConf, set(
		_, 
		Matcher<const RdKafka::Conf*>(_pTopic), 
		StrEq("")))
		.Times(0);
	EXPECT_CALL(*_pConf, set(
		_, 
		Matcher<const RdKafka::Conf*>(_pConf), 
		StrEq("")))
		.Times(0);
	EXPECT_CALL(*_pConf, set(
		StrEq("default_topic_conf"), 
		Matcher<const RdKafka::Conf*>(_pTopic), 
		StrEq("")))
		.Times(0);

	KafkaConf::get(_pConfig, _pConf, _pTopic);
}

TEST_F(test_kafka_conf, one_option_supplied)
{
	Utils::KeyValue options;

	options["aunty"] = "alice";

	ON_CALL(*_pConfig, getClientOptions())
		.WillByDefault(ReturnRef(options));
	EXPECT_CALL(*_pConf, set(
		Matcher<const std::string&>("aunty"), 
		Matcher<const std::string&>("alice"), 
		Matcher<std::string&>(_)))
		.Times(1);
	EXPECT_CALL(*_pConf, set(
		StrEq("default_topic_conf"), 
		Matcher<const RdKafka::Conf*>(_pTopic), 
		StrEq("")))
		.Times(0);

	KafkaConf::get(_pConfig, _pConf, _pTopic);
}

TEST_F(test_kafka_conf, two_option_supplied)
{
	Utils::KeyValue options;

	options["aunty"] = "alice";
	options["uncle"] = "david";

	ON_CALL(*_pConfig, getClientOptions())
		.WillByDefault(ReturnRef(options));
	EXPECT_CALL(*_pConf, set(
		Matcher<const std::string&>("aunty"), 
		Matcher<const std::string&>("alice"), 
		Matcher<std::string&>(_)))
		.Times(1);
	EXPECT_CALL(*_pConf, set(
		Matcher<const std::string&>("uncle"), 
		Matcher<const std::string&>("david"), 
		Matcher<std::string&>(_)))
		.Times(1);
	EXPECT_CALL(*_pConf, set(
		StrEq("default_topic_conf"), 
		Matcher<const RdKafka::Conf*>(_pTopic), 
		StrEq("")))
		.Times(0);

	KafkaConf::get(_pConfig, _pConf, _pTopic);
}

TEST_F(test_kafka_conf, one_topic_option_supplied)
{
	Utils::KeyValue options;

	options["topic.father"] = "ted";

	ON_CALL(*_pConfig, getClientOptions())
		.WillByDefault(ReturnRef(options));
	EXPECT_CALL(*_pTopic, set(
		Matcher<const std::string&>("father"), 
		Matcher<const std::string&>("ted"), 
		Matcher<std::string&>(_)))
		.Times(1);
	EXPECT_CALL(*_pConf, set(
		StrEq("default_topic_conf"), 
		Matcher<const RdKafka::Conf*>(_pTopic), 
		StrEq("")))
		.Times(1);

	KafkaConf::get(_pConfig, _pConf, _pTopic);
}

TEST_F(test_kafka_conf, one_of_each_option_supplied)
{
	Utils::KeyValue options;

	options["aunty"] = "alice";
	options["uncle"] = "david";
	options["topic.father"] = "ted";

	ON_CALL(*_pConfig, getClientOptions())
		.WillByDefault(ReturnRef(options));

	EXPECT_CALL(*_pConf, set(
		Matcher<const std::string&>("aunty"), 
		Matcher<const std::string&>("alice"), 
		Matcher<std::string&>(_)))
		.Times(1);
	EXPECT_CALL(*_pConf, set(
		Matcher<const std::string&>("uncle"), 
		Matcher<const std::string&>("david"), 
		Matcher<std::string&>(_)))
		.Times(1);
	EXPECT_CALL(*_pTopic, set(
		Matcher<const std::string&>("father"), // expect "topic." stripped
		Matcher<const std::string&>("ted"), 
		Matcher<std::string&>(_)))
		.Times(1);
	EXPECT_CALL(*_pConf, set(
		StrEq("default_topic_conf"), 
		Matcher<const RdKafka::Conf*>(_pTopic), 
		StrEq("")))
		.Times(1);

	KafkaConf::get(_pConfig, _pConf, _pTopic);
}

TEST_F(test_kafka_conf, anon_test_options_supplied)
{
	Utils::KeyValue options;

	options["aunty"] = "alice";
	options["uncle"] = "david";
	options["topic.father"] = "ted";

	ON_CALL(*_pConfig, getClientOptions())
		.WillByDefault(ReturnRef(options));
	EXPECT_CALL(*_pConf, set(
		Matcher<const std::string&>(_), 
		Matcher<const std::string&>(_), 
		Matcher<std::string&>(_)))
		.Times(2);
	EXPECT_CALL(*_pTopic, set(
		Matcher<const std::string&>(_), 
		Matcher<const std::string&>(_), 
		Matcher<std::string&>(_)))
		.Times(1);
	EXPECT_CALL(*_pConf, set(
		StrEq("default_topic_conf"), 
		Matcher<const RdKafka::Conf*>(_pTopic), 
		StrEq("")))
		.Times(1);

	KafkaConf::get(_pConfig, _pConf, _pTopic);
}

TEST_F(test_kafka_conf, group_id_test_options_supplied)
{
	Utils::KeyValue options;

	options["aunty"] = "alice";
	options["uncle"] = "david";
	options["group.id"] = "mytestgroupid";
	options["topic.father"] = "ted";

	ON_CALL(*_pConfig, getClientOptions())
		.WillByDefault(ReturnRef(options));

	EXPECT_CALL(*_pConf, set(
		Matcher<const std::string&>(_), 
		Matcher<const std::string&>(_), 
		Matcher<std::string&>(_)))
		.Times(2); // alice and david
	EXPECT_CALL(*_pConf, set(
		Matcher<const std::string&>("group.id"), 
		Matcher<const std::string&>("mytestgroupid"), 
		Matcher<std::string&>(_)))
		.Times(1);
	EXPECT_CALL(*_pConf, set(
		Matcher<const std::string&>("offset.store.method"), 
		Matcher<const std::string&>("broker"), 
		Matcher<std::string&>(_)))
		.Times(1);
	EXPECT_CALL(*_pTopic, set(
		Matcher<const std::string&>(_), 
		Matcher<const std::string&>(_), 
		Matcher<std::string&>(_)))
		.Times(1);
	EXPECT_CALL(*_pConf, set(
		StrEq("default_topic_conf"), 
		Matcher<const RdKafka::Conf*>(_pTopic), 
		StrEq("")))
		.Times(1);

	KafkaConf::get(_pConfig, _pConf, _pTopic);
}

TEST_F(test_kafka_conf, anon_test_options_supplied_default_conf)
{
	Utils::KeyValue options;

	options["aunty"] = "alice";
	options["uncle"] = "david";

	// Since we don't suppy the mock topic config in this
	// unit test a standard rdkafka object will be created
	// so to avoid rdkafka exceptions we need to supply a
	// real named conf key and value.
	options["topic.auto.offset.reset"] = "smallest";

	ON_CALL(*_pConfig, getClientOptions())
		.WillByDefault(ReturnRef(options));
	EXPECT_CALL(*_pConf, set(
		Matcher<const std::string&>(_), 
		Matcher<const std::string&>(_), 
		Matcher<std::string&>(_)))
		.Times(2);
	EXPECT_CALL(*_pConf, set(
		StrEq("default_topic_conf"), 
		Matcher<const RdKafka::Conf*>(_), 
		StrEq("")))
		.Times(1);

	KafkaConf::get(_pConfig, _pConf, _pTopic);
}

TEST_F(test_kafka_conf, expect_exception_invalid_args)
{
	Utils::KeyValue options;

	options["topic.this"] = "should cause an exception";

	ON_CALL(*_pConfig, getClientOptions())
		.WillByDefault(ReturnRef(options));
	EXPECT_CALL(*_pConf, set(
		Matcher<const std::string&>(_), 
		Matcher<const std::string&>(_), 
		Matcher<std::string&>(_)))
		.Times(0);
	EXPECT_CALL(*_pConf, set(
		StrEq("default_topic_conf"), 
		Matcher<const RdKafka::Conf*>(_), 
		StrEq("")))
		.Times(0);

	try {
		// no mock _pTopic causes exception
		KafkaConf::get(_pConfig, _pConf); 
		FAIL() << "expected std::invalid_argument*";
	}
	catch(std::invalid_argument *e) {
		std::string expect("Configure failure at line");
		std::string what(e->what());
		std::string actual = what.substr(0, expect.size());
		ASSERT_EQ(expect, actual);
	}
	catch(...) {
		FAIL() << "Incorrect/unknown exception thrown";
	}
}

