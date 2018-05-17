#pragma once

#include <memory>
#include <sstream>
#include <iostream>
#include <librdkafka/rdkafkacpp.h>

#include "curlwrapper.hpp"
#include "hexdump.hpp"
#include "config/abstract_config.hpp"


class Consume :  
	public RdKafka::ConsumeCb,
	protected KafkaUtils::Hexdump
{
public:
	typedef std::shared_ptr<ConsumeCb> ShPtr;

	Consume();
	virtual ~ConsumeCb();

	virtual Consume&
        setOutputStream(std::ostream *pstream) 
	{ _poutput = pstream; return *this; }

	virtual Consume&
	setHexdump(bool f) 
	{ _hexdump = f; return *this; }

	virtual Consume&
	setSendMessage(bool f) 
	{ _sendmessage = f; return *this; }

	virtual Consume&
	setConfig(AbstractConfig *p) 
	{ _pconfig = p; return *this; }

	virtual void
        consume_cb(RdKafka::Message&, void*);

	static size_t bodyWriteCallback(char*, size_t, size_t, void*);
	static size_t headerWriteCallback(char*, size_t, size_t, void*);

protected:

	bool		 _hexdump;
	bool		 _sendmessage;
	std::ostream    *_poutput;
	AbstractConfig	*_pconfig;
	CurlWrapper	*_pcurl;

	void init();

	void hexdumpMessage(RdKafka::Message&);

	bool sendMessage(RdKafka::Message&);


}; // class Consume

