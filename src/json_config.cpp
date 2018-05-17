
#include <sstream>
#include <stdexcept>
#include "json_config.hpp" 

int
JsonConfig::load(json_t *pjsonconfig)
{
	if(!json_is_object(pjsonconfig)) {
		throw std::invalid_argument("JSON is not an OBJECT");
	}
	load_consumer(pjsonconfig);
	load_callback(pjsonconfig);
	_verified = true;
	return 0;
}

void
JsonConfig::load_consumer(json_t *pjsonconfig)
{
	json_t *pconsumer, *pgroup;
	if((pconsumer = json_object_get(pjsonconfig, "consumer")) != NULL) {
		load_consumer_brokers(json_object_get(pconsumer, "brokers"));
		load_consumer_options(json_object_get(pconsumer, "options"));
		load_consumer_topic(json_object_get(pconsumer, "topic"));
	}
	else {
		throw std::invalid_argument("consumer not found");
	}
}

void
JsonConfig::load_consumer_brokers(json_t *pjsonbrokers)
{
	int broker_count = 0;
	if(pjsonbrokers && json_is_array(pjsonbrokers)) {
		size_t index;
		json_t *pvalue;
		json_array_foreach(pjsonbrokers, index, pvalue) {
			const char *pstr = json_string_value(pvalue);
			_brokers.push_back(std::string(pstr));	
			broker_count++;
		}
	}
	if(broker_count == 0) {	
		throw std::invalid_argument("No brokers supplied");
	}
}

void
JsonConfig::load_consumer_options(json_t *pjsonoptions)
{
	if(pjsonoptions && json_is_array(pjsonoptions)) {
		size_t index;
		json_t *pvalue;
		json_array_foreach(pjsonoptions, index, pvalue) {
			if(json_is_object(pvalue)) {
				json_t
				  *p1 = json_object_get(pvalue, "name"),
				  *p2 = json_object_get(pvalue, "value");
				if(p1 && json_is_string(p1) && p2 && json_is_string(p2)) {
					_options[ std::string(json_string_value(p1)) ] = 
						std::string(json_string_value(p2));
				}
			}
		}	
	}
}

void
JsonConfig::load_consumer_topic(json_t *pjsontopic)
{
	int topic_count = 0;
	if(pjsontopic && json_is_object(pjsontopic)) {
		json_t *p = json_object_get(pjsontopic, "name");
		if(p && json_is_string(p)) {
			_topic = std::string(json_string_value(p));
			topic_count++;
		}
		_partition = 0; // Default to partition zero, unless...
		p = json_object_get(pjsontopic, "partition");
		if(p && json_is_integer(p)) {
			_partition = (int)json_integer_value(p);
		}
	}
	if(topic_count == 0) {
		throw std::invalid_argument("No topic name supplied");
	}
}

void
JsonConfig::load_callback(json_t *pjsonconfig)
{
	json_t *ptop, *ptemp;

	if(!(ptop = json_object_get(pjsonconfig, "callback"))) {
		throw std::invalid_argument("callback not found");
	}
	if((ptemp = json_object_get(ptop, "username")) && json_is_string(ptemp)) {
		_username = std::string(json_string_value(ptemp));
	}
	if((ptemp = json_object_get(ptop, "password")) && json_is_string(ptemp)) {
		_password = std::string(json_string_value(ptemp));
	}
	if((ptemp = json_object_get(ptop, "url")) && json_is_string(ptemp)) {
		_apiUrl = std::string(json_string_value(ptemp));
	}
	else {
		throw std::invalid_argument("No callback URL supplied");
	}
	if((ptemp = json_object_get(ptop, "expect_response_code")) && json_is_string(ptemp)) {
		_expectResponseCode = std::string(json_string_value(ptemp));
	}
	else {
		_expectResponseCode = 200;
	}
	if((ptemp = json_object_get(ptop, "httpverb")) && json_is_string(ptemp)) {
		_httpVerb = std::string(json_string_value(ptemp));
	}
	else {
		_httpVerb = std::string("PUT");
	}
	if((ptemp = json_object_get(ptop, "content-type")) && json_is_string(ptemp)) {
		std::string s(json_string_value(ptemp));
		_contentType = s;
	}
	else {
		_contentType = std::string("application/octet-stream");
	}
	if((ptemp = json_object_get(ptop, "headers")) && json_is_array(ptemp)) {
		size_t index;
		json_t *pvalue;
		json_array_foreach(ptemp, index, pvalue) {
			if(json_is_object(pvalue)) {
				json_t 
				  *p1 = json_object_get(pvalue, "name"), 
				  *p2 = json_object_get(pvalue, "value");
				if(p1 && json_is_string(p1) && p2 && json_is_string(p2)) {
					_requestHeaders[ std::string(json_string_value(p1)) ] = 
						std::string(json_string_value(p2));
				}
			}
		}
	}
}

int
JsonConfig::loadFromFile(const std::string &filename)
{
	int rval = -1;
	json_error_t err;
	json_t *pjsonconfig = json_load_file(filename.c_str(), 0, &err);
	if(!pjsonconfig) {
		std::stringstream oss;
		oss << err.text << " at line " << err.line << " in column " << err.column;
		throw std::invalid_argument(oss.str().c_str());
	}
	try {
		rval = load(pjsonconfig);
	}
	catch(std::invalid_argument e) {
		rval = -2;
	}
	json_decref(pjsonconfig);
	return rval;
}

int 
JsonConfig::loadFromString(const std::string &json)
{
	int rval;
	json_error_t err;
	json_t *pjsonconfig = json_loads(json.c_str(), 0, &err);
	if(!pjsonconfig) {
		std::stringstream oss;
		oss << err.text << " at line " << err.line << " in column " << err.column;
		throw std::invalid_argument(oss.str().c_str());
	}
	rval = load(pjsonconfig);
	json_decref(pjsonconfig);
	return rval;
}

JsonConfigFromFile::JsonConfigFromFile(const std::string &filename)
{
	loadFromFile(filename); // Used for runtime
}

JsonConfigFromString::JsonConfigFromString(const std::string &json)
{
	loadFromString(json); // Used for unit testing
}


