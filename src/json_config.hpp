#pragma once

#include <jansson.h>
#include "abstract_config.hpp" 

class JsonConfig : public AbstractConfig
{
public:
	int loadFromFile(const std::string &filename); 
	int loadFromString(const std::string &json);

private:
	int  load(json_t *pjson);
	void load_consumer(json_t *pjson);
	void load_consumer_topic(json_t *pjson);
	void load_consumer_brokers(json_t *pjson);
	void load_consumer_options(json_t *pjson);
	void load_callback(json_t *pjson);
};

class JsonConfigFromFile : public JsonConfig
{
public:
	JsonConfigFromFile(const std::string &filename);
};

class JsonConfigFromString : public JsonConfig
{
public:
	JsonConfigFromString(const std::string &json);
};


