#pragma once

#include <string>

namespace KafkaUtils {

class Hexdump 
{
protected:
	virtual std::string
	hexdump(void*, size_t);
}; // class Hexdump

}; // namespace KafkaUtils

