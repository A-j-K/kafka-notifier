
#include <cctype>
#include <cstdio>
#include <cstring>
#include <stdexcept>

#include <unistd.h>

#include "utils.hpp"
#include "gkw_consume_cb.hpp"

Consume::Consume() :
	_hexdump(false),
	_poutput(&std::cout),
	_pcurl(new CurlWrapper))
{}

Consume::~Consume()
{
	if(_pcurl) delete _pcurl;
}

void
Consume::consume_cb(RdKafka::Message &inmsg, void *inpuserdata)
{
	int retry_counter = 5;
	switch(inmsg.err()) {
		case RdKafka::ERR__TIMED_OUT:
			(*_poutput) << "Callback timed out\n";
			break;
		case RdKafka::ERR_NO_ERROR:
			if(_hexdump) {
				hexdumpMessage(inmsg);
			}
			if(_sendmessage) {
				while(!sendMessage(inmsg) && retry_counter--) {
					usleep(250); // ToDo, exponetial backoff instead
				}
				if(retry_counter < 1) {
					throw new std::runtime_error("API callback retry count exceeded");
				}
			}
			break;		
		default:
			(*_poutput) << "Other\n";
			break;
	}
}

size_t 
Consume::bodyWriteCallback(char *buf, size_t len, size_t nmemb, void *puserdata)
{
	size_t actual_size = len * nmemb;
	CurlBody *p = reinterpret_cast<CurlBody*>(puserdata);
	p->addBody(buf, actual_size);
	return actual_size;
}

size_t 
Consume::headerWriteCallback(char *buf, size_t len, size_t nmemb, void *puserdata)
{
	size_t actual_size = len * nmemb;
	CurlHeader *p = reinterpret_cast<CurlHeader*>(puserdata);
	p->addHeader(buf, actual_size);
	return actual_size;
}

bool
Consume::sendMessage(RdKafka::Message &inmsg)
{
	CURLcode result;
	std::string temp;
	std::stringstream oss;
	curl_slist *pheaders = NULL;
	Utils::KeyValue headers = _pconfig->getRequestHeaders();
	Utils::KeyValue::iterator itor = headers.begin();

	CurlBody::ShPtr spbody     = CurlBody::ShPtr(new CurlBody);
	CurlHeader::ShPtr spheader = CurlHeader::ShPtr(new CurlHeader);

	_spwcurl->recycle();
	_spwcurl->setHeader("Connection: keep-alive");
	_spwcurl->setHeader("User-Agent: Kafka-Notifier-0.1.0");
	_spwcurl->setHeader("Content-Type: application/octet-stream");
	_spwcurl->setHeader("Accept:");
	while(itor != headers.end()) {
		_spwcurl->setHeader(itor->first + ": " + itor->second);
		itor++;
	}
	_spwcurl->setHeader("X-Kafka-Topic: " + inmsg.topic_name());
	_spwcurl->setHeader("X-Kafka-Partition: " + inmsg.partition());
	oss << "X-Kafka-Offset: " << inmsg.offset();
	_spwcurl->setHeader(oss.str());
	temp.append((char*)inmsg.key_pointer(), (size_t)inmsg.key_len());
	_spwcurl->setHeader("X-Kafka-Key: " + temp);
	_spwcurl->setWriteFunction(Consume::bodyWriteCallback);
	_spwcurl->setWriteData((void*)spbody.get());
	_spwcurl->setHeaderFunction(Consume::headerWriteCallback);
	_spwcurl->setHeaderData((void*)spheader.get());
	_spwcurl->setData(inmsg.payload(), inmsg.len());
	if(_pconfig->getUsername().size() > 0) {
		_spwcurl->setUsername(_pconfig->getUsername());
	}
	if(_pconfig->getPassword().size() > 0) {
		_spwcurl->setPassword(_pconfig->getPassword());
	}
	_spwcurl->setUrl(_pconfig->getApiUrl());
	_spwcurl->setVerb(_pconfig->getHttpVerb());
	result = _spwcurl->perform();	
	spheader->dumpToStream(_poutput);
	spbody->dumpToStream(_poutput);
	if(result == CURLE_OK && !spheader->isEmpty()) {
		std::string line0 = spheader->getHeader(0).substr(0, _pconfig->getExpectResponseCode().size());
		if(line0 != _pconfig->getExpectResponseCode()) {
			std::stringstream oss;
			oss << "Header: " << line0 << std::endl << "Expected: " << _pconfig->getExpectResponseCode() << std::endl;
			(*_poutput) << oss.str();
			throw new std::logic_error(oss.str());
		}
	}
	return result == CURLE_OK;
}

void 
Consume::hexdumpMessage(RdKafka::Message &inmsg)
{
	std::stringstream oss;
	std::string message_key;
	message_key.append((char*)inmsg.key_pointer(), (size_t)inmsg.key_len());
	oss << "CB Comsume : message\n";
	oss << "Message Key: " << message_key << std::endl;
	oss << "Topic      : " << inmsg.topic_name() << std::endl;
	oss << "Partition  : " << inmsg.partition() << std::endl;
	oss << "Offset     : " << inmsg.offset() << std::endl;
	oss << hexdump(inmsg.payload(), inmsg.len());
	(*_poutput) << oss.str() << std::endl;
}


