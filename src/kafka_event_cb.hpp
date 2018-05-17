#pragma once

#include <sstream>
#include <iostream>
#include "utils.hpp"

class KafkaEventCallback : public RdKafka::EventCb
{
protected:

	std::ostream	*_poutput;

public:
	
	KafkaEventCallback();
	~KafkaEventCallback();

	KafkaEventCallback(std::ostream *pstream) : _poutput(&std::cout) {}

	virtual void 
	event_cb(RdKafka::Event &event); 

	virtual KafkaEventCallback&
	setOutputStream(std::ostream *pstream); 
};


