
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <exception>

#include "utils.hpp"
#include "kafka_conf.hpp"

KafkaConf::KafkaConf()
{}

KafkaConf::~KafkaConf()
{}

RdKafka::Conf *
KafkaConf::get(const AbstractConfig *inpConfig, RdKafka::Conf *outpConf,
	RdKafka::Conf *pTopic)
{
	bool add_topic = false, and_then_delete_topic = false;
	std::string errstr;
	RdKafka::Conf::ConfResult result;

	if(!outpConf) {
		outpConf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
	}

	Utils::KeyValue options = inpConfig->getClientOptions();
	Utils::KeyValue::const_iterator itor_options = options.begin();

	while(itor_options != options.end()) {
		size_t topic_pos;
		std::string name = itor_options->first;
		std::string value = itor_options->second;
		topic_pos = name.find("topic.", 0);
		if(topic_pos != std::string::npos && topic_pos == 0) {
			std::string newname = name.substr(sizeof("topic.")-1);
			add_topic = true;
			if(!pTopic) {
				pTopic = RdKafka::Conf::create(RdKafka::Conf::CONF_TOPIC);
				and_then_delete_topic = true;
			}
			result = pTopic->set(newname, value, errstr);
			if(result != RdKafka::Conf::ConfResult::CONF_OK) {
				throw new std::invalid_argument(
					stringbuilder()
					<< "Configure failure at line "
					<< __LINE__ << " " << errstr
				);
			}
		}
		else {
			result = outpConf->set(name, value, errstr);
			if(result != RdKafka::Conf::ConfResult::CONF_OK) {
				throw new std::invalid_argument(
					stringbuilder()
					<< "Configure failure at line "
					<< __LINE__ << " " << errstr
				);
			}
		}
		if(name == "group.id") {
			outpConf->set("offset.store.method", "broker", errstr);
		}
		itor_options++;
	}

	outpConf->set("enable.auto.commit", "false", errstr);
	outpConf->set("auto.commit.interval.ms", "0", errstr);

	if(add_topic && pTopic) {
		outpConf->set(std::string("default_topic_conf"), pTopic, errstr);
		if(and_then_delete_topic) delete pTopic;
	}
	return outpConf;
}

