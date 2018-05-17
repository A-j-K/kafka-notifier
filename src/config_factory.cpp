
#include "config_factory.hpp" 
#include "json_config.hpp"


AbstractConfig::ShPtr
ConfigFactory::getConfigByFile(const std::string &filename)
{
	return AbstractConfig::ShPtr(new JsonConfigFromFile(filename));
}

AbstractConfig::ShPtr
ConfigFactory::getConfigByJsonString(const std::string &json)
{
	return AbstractConfig::ShPtr(new JsonConfigFromString(json));
}



