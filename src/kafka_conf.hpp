#pragma once

#include <librdkafka/rdkafkacpp.h>

#include "utils.hpp"
#include "config/abstract_config.hpp"

class KafkaConf
{
public:
	KafkaConf(); 
	virtual ~KafkaConf();

	static RdKafka::Conf *
	get(const AbstractConfig*, RdKafka::Conf *outpConf, RdKafka::Conf *pTopic=0);
};

