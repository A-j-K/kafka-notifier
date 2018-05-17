
#include <cstdio>

#include "kafka_event_cb.hpp"

KafkaEventCallback::KafkaEventCallback()
{
	_poutput = &(std::cout);
}

KafkaEventCallback::~KafkaEventCallback()
{}


KafkaEventCallback&
KafkaEventCallback::setOutputStream(std::ostream *pstream) { 
	_poutput = pstream; 
	return *this; 
}


void 
KafkaEventCallback::event_cb(RdKafka::Event &event) 
{
	RdKafka::Event::Type type = event.type();
	switch(type) {

	case RdKafka::Event::EVENT_ERROR:
		(*_poutput) << "ERROR: (" << RdKafka::err2str(event.err()) 
				<< "): " << event.str() << std::endl;
		if(event.err() == RdKafka::ERR__ALL_BROKERS_DOWN) {
			(*_poutput) << "FATAL: Bailing out" << std::endl;
				throw new std::runtime_error(
					stringbuilder()
					<< "Brokers are down? "
					<< event.str()	
				);
		}
		break;

	case RdKafka::Event::EVENT_STATS:
		(*_poutput) << "STATS: " << event.str() << std::endl;
		break;

	case RdKafka::Event::EVENT_LOG:
		 (*_poutput) << "LOG-" << event.severity() << "-" << event.fac() 
			<< ": " << event.str() << std::endl;
		break;

	case RdKafka::Event::EVENT_THROTTLE:
		(*_poutput) << "THROTTLE: " << event.throttle_time() << "ms " 
			<< event.broker_name() 
			<< " id " << (int)event.broker_id() << std::endl;
		break;

	default:
		(*_poutput) << "EVENT: " << event.type() << " (" 
			<< RdKafka::err2str(event.err()) << "): " 
			<< event.str() << std::endl;
		break;

	// End switch.
	}
}


