#pragma once

#include <memory>
#include <string>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "config/abstract_config.hpp"

class MockAbstractConfig : public AbstractConfig
{
public:
	typedef std::shared_ptr<MockAbstractConfig> ShPtr;
	MOCK_CONST_METHOD0(getPartition, int());
	MOCK_CONST_METHOD0(getTopic, std::string());
	MOCK_CONST_METHOD0(getBrokers, const Utils::StringVector&());
	MOCK_CONST_METHOD0(getClientOptions, const Utils::KeyValue&());
	MOCK_CONST_METHOD0(getBrokersAsString, std::string());
	MOCK_CONST_METHOD0(getExpectResponseCode, int());
	MOCK_CONST_METHOD0(getApiUrl, const std::string&());
	MOCK_CONST_METHOD0(getRequestHeaders, const Utils::KeyValue&());
	MOCK_CONST_METHOD0(getHttpVerb, const std::string());	
	MOCK_CONST_METHOD0(getContentType, const std::string());
};

