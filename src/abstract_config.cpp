
#include <sstream>
#include "abstract_config.hpp"

AbstractConfig::AbstractConfig() : _verified(false) 
{}

std::string
AbstractConfig::getBrokersAsString(void) const
{ 
	bool skipfirst = true;
	std::string rval;
	std::stringstream oss;
	Utils::StringVector::const_iterator itor = _brokers.begin();
	while(itor != _brokers.end()) {
		if(!skipfirst) {
			oss << ",";
		}
		oss << *itor;
		skipfirst = false;	
		itor++;
	}
	return oss.str(); 
}

