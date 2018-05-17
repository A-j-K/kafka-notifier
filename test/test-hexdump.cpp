
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "hexdump.hpp"

class test_hexdump : public ::testing::Test, protected KafkaUtils::Hexdump
{
public:
	virtual void SetUp() {}
	virtual void TearDown() {}
};


TEST_F(test_hexdump, simple)
{
	char sut[] = "abcdefghijklmnopqrstuvwxyz";
	std::string expect(
		"0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f   |0123456789abcdef|\n"
		"61 62 63 64 65 66 67 68 69 6a 6b 6c 6d 6e 6f 70  |abcdefghijklmnop|\n"
		"71 72 73 74 75 76 77 78 79 7a                    |qrstuvwxyz      |\n"
		"0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f   |0123456789abcdef|\n"
	);
	std::string actual = hexdump(sut, sizeof(sut)-1);
	EXPECT_EQ(expect, actual);
}

