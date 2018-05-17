
#include <cctype>
#include <sstream>
#include <iomanip>

#include "hexdump.hpp"

namespace KafkaUtils {

std::string
Hexdump::hexdump(void *s, size_t len)
{
	size_t i, line = 0, offset = 0;
	const char *p = static_cast<const char*>(s);
	std::stringstream out;

	out << "          0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f  |0123456789abcdef|" << std::endl;
	for (offset = 0 ; offset < len ; offset += 16, line+=16) {
		int charcount = 16;
		out << std::setw(8) << std::setfill('0') << std::right << std::hex << line << std::left << " ";
		for (i = offset ; i < ((int)offset+16) && i < (int)len ; i++, charcount--) {
			std::stringstream oss;
			oss << std::setw(2) << std::hex << ((int)(p[i] & 0xff)) << " ";
			out << oss.str();
		}
		while(charcount-- > 0) {
			out << "   ";
		}
		out << " |";
		charcount = 16;
		for (i = offset ; i < ((int)offset+16) && i < (int)len ; i++, charcount--) {
			std::stringstream oss;
			oss << ((char)(std::isprint(p[i]) ? p[i] : '.'));
			out << oss.str();
		}
		while(charcount-- > 0) {
			out << " ";
		}
		out << "|";
		out << std::endl;
	}
	return out.str();
}

}; // namespace KafkaUtils
