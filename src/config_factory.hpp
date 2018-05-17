#pragma once

#include "abstract_config.hpp" 

class ConfigFactory
{
public:
	static AbstractConfig::ShPtr
	getConfigByFile(const std::string &filename); 

	static AbstractConfig::ShPtr
	getConfigByJsonString(const std::string &json); 
};


