#pragma once

#include <memory>
#include <sstream>
#include <iostream>
#include <librdkafka/rdkafkacpp.h>

#include "hexdump.hpp"

namespace gkw {

class EventCb :  
	public RdKafka::EventCb,
	protected KafkaUtils::Hexdump
{
public:
	typedef std::shared_ptr<EventCb> ShPtr;

	std::ostream    *_poutput;

	EventCb();
	~EventCb();
	EventCb(std::ostream *pstream);

	virtual EventCb&
	setOutputStream(std::ostream *pstream);

	virtual void
	event_cb(RdKafka::Event&);

}; // class EventCb

}; // namespace gkw
