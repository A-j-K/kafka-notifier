
#include <cctype>
#include <cstdio>
#include <cstring>

#include "utils.hpp"
#include "event_cb.hpp"

namespace gkw {

EventCb::EventCb() :
	_poutput(&std::cout)
{}

EventCb::~EventCb()
{}

EventCb::EventCb(std::ostream *pstream) :
	_poutput(pstream) 
{}



EventCb&
EventCb::setOutputStream(std::ostream *pstream)
{
	_poutput = pstream;
	return *this;
}

void
EventCb::event_cb(RdKafka::Event &inEvent)
{
	std::stringstream oss;

	switch(inEvent.type()) {
		case RdKafka::Event::EVENT_ERROR:
			(*_poutput) << "CB Error (" << RdKafka::err2str(inEvent.err()) << "): " << inEvent.str() << "\n";
			break;
		case RdKafka::Event::EVENT_STATS:
			(*_poutput) << "Stats: " << inEvent.str() << std::endl;
			break;		
		default:
			(*_poutput) << "CB Other: " << RdKafka::err2str(inEvent.err()) << "): " << inEvent.str() << "\n";
	}
}

}; // namespace gkw

