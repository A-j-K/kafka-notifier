#pragma once

#include <memory>
#include <string>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <curl/curl.h>

#include "utils.hpp"
#include "curler.hpp"

class MockCurler : public Curler
{
public:
	typedef std::shared_ptr<MockCurler> ShPtr;
	MOCK_METHOD3(send, CurlerRval::ShPtr(char*,int,Utils::StringVector&));
	MOCK_METHOD1(xlateCode2str, std::string(CURLcode));
};

