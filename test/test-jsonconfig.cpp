
#include <string>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "config/config_factory.hpp"

static const char 
*ptest_str = R"END(
{
	"consumer": {
		"brokers": [
			"foo-1.com:443",
			"foo-2.com:443"
		],
		"topic": {
			"name": "topicname",
			"partition": 10
		},
		"options": [
			{ "name": "group.id",           "value": "mycustomergroup" },
			{ "name": "security.mechanism", "value": "sasl_ssl" },
			{ "name": "sasl_username",      "value": "testuser" },
			{ "name": "sasl_password",      "value": "testpass" }
		]
	},
	"callback": {
		"url": "https://bar.com/baz",
		"httpverb": "POST",
		"content-type": "application/JSON",
		"expect_response_code": "HTTP/1.1 200 OK",
		"username": "testuser",
		"password": "testpass",
		"headers": [
			{ "name": "X-Request-1", "value": "humbug-1" },
			{ "name": "X-Request-2", "value": "humbug-2" }
		]
	}
}
)END";

class test_jsonconfig : public ::testing::Test
{
public:
	AbstractConfig::ShPtr _spConfig;
	virtual void SetUp() {
		std::string s(ptest_str);
		_spConfig = ConfigFactory::getConfigByJsonString(s);
	}
	virtual void TearDown() {}
};


TEST_F(test_jsonconfig, consumer_brokers)
{
	Utils::StringVector expect;
	expect.push_back(std::string("foo-1.com:443"));
	expect.push_back(std::string("foo-2.com:443"));
	Utils::StringVector brokers = _spConfig->getBrokers();
	EXPECT_THAT(brokers, ::testing::ContainerEq(expect));
}

TEST_F(test_jsonconfig, consumer_brokers_as_string)
{
	ASSERT_EQ(
		std::string("foo-1.com:443,foo-2.com:443"),
		_spConfig->getBrokersAsString()
	);
}

TEST_F(test_jsonconfig, consumer_broker_options)
{
	Utils::KeyValue options = _spConfig->getClientOptions();
	ASSERT_EQ(std::string("sasl_ssl"), options["security.mechanism"]);
	ASSERT_EQ(std::string("testuser"), options["sasl_username"]);
	ASSERT_EQ(std::string("testpass"), options["sasl_password"]);
}

TEST_F(test_jsonconfig, consumer_topicname)
{
	ASSERT_EQ(
		std::string("topicname"), 
		_spConfig->getTopic()
	);
}

TEST_F(test_jsonconfig, consumer_topic_partition)
{
	ASSERT_EQ(10, _spConfig->getPartition());
}


TEST_F(test_jsonconfig, consumer_callback_url)
{
	ASSERT_EQ(
		std::string("https://bar.com/baz"), 
		_spConfig->getApiUrl()
	);
}

TEST_F(test_jsonconfig, consumer_callback_httpverb)
{
	ASSERT_EQ(
		std::string("POST"), 
		_spConfig->getHttpVerb()
	);
}

TEST_F(test_jsonconfig, consumer_callback_username)
{
	ASSERT_EQ(
		std::string("testuser"), 
		_spConfig->getUsername()
	);
}

TEST_F(test_jsonconfig, consumer_callback_password)
{
	ASSERT_EQ(
		std::string("testpass"), 
		_spConfig->getPassword()
	);
}

TEST_F(test_jsonconfig, consumer_callback_content_type)
{
	ASSERT_EQ(
		std::string("application/JSON"), 
		_spConfig->getContentType()
	);
}

TEST_F(test_jsonconfig, consumer_callback_expect_response_code)
{
	ASSERT_EQ("HTTP/1.1 200 OK", _spConfig->getExpectResponseCode());
}

TEST_F(test_jsonconfig, consumer_callback_headers)
{
	Utils::KeyValue headers = _spConfig->getRequestHeaders();
	ASSERT_EQ(std::string("humbug-1"), headers["X-Request-1"]);
	ASSERT_EQ(std::string("humbug-2"), headers["X-Request-2"]);
}

