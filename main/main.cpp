
#include <string>
#include <vector>
#include <csignal>
#include <iostream>

#include "kafka_conf.hpp"
#include "config/config_factory.hpp"
#include "event_cb.hpp"
#include "gkw_consume_cb.hpp"

static bool run_system;

static void 
sigterm(int sig) 
{
	run_system = false;
}

int
main(int argc, char *argv[])
{
	int rval = 0;

	std::string errstr;
	std::vector<std::string> topics;
	RdKafka::Conf *pKafkaConf = 0;
	RdKafka::Conf::ConfResult result;
	AbstractConfig::ShPtr spConfig;
	RdKafka::KafkaConsumer *pConsumer = NULL;

	signal(SIGINT, sigterm);
	signal(SIGTERM, sigterm);

	try {
		spConfig = ConfigFactory::getConfigByFile(std::string("/etc/notifier.json"));
		pKafkaConf = KafkaConf::get(spConfig.get(), 0);
		auto spEventCb = gkw::EventCb::ShPtr(new gkw::EventCb());
		auto spConsumeCb = GkwConsumeCb::ShPtr(new GkwConsumeCb());
		spConsumeCb->setConfig(spConfig.get());
		spConsumeCb->setHexdump(true);
		spConsumeCb->setSendMessage(true);
		
		pKafkaConf->set("event_cb", spEventCb.get(), errstr);
		pConsumer = RdKafka::KafkaConsumer::create(pKafkaConf, errstr);
		if(!pConsumer) {
			std::cout << "Consumer error: " << errstr << "\n";
		}
		topics.push_back(spConfig->getTopic());
		pConsumer->subscribe(topics);

		run_system = true;
		while(run_system) {
			int retries = 0;
			RdKafka::Message *pmsg;
			if((pmsg = pConsumer->consume(1000)) != NULL) {
				switch(pmsg->err()) {
					case RdKafka::ERR__TIMED_OUT:
						//std::cout << "Main loop timed out waiting for messages." << std::endl;
						break;
					case RdKafka::ERR_NO_ERROR:
						spConsumeCb->consume_cb(*pmsg, NULL); 
						pConsumer->commitAsync(pmsg);
						break;
					default:
						std::cout
							<< "Topic: " << pmsg->topic_name() << " " 
							<< "Partition: " << pmsg->partition() << " \""
							<< pmsg->errstr() << "\""
							<< std::endl;
						break;
				}
				delete pmsg; 
			}
		}
		std::cout << "System shutting down" << std::endl;
	}
	catch(std::invalid_argument *e) {
		std::cout << "Invald ARG eerror: " << e->what() << "\n";
		rval = -1;
	}
	catch(std::exception e) {
		std::cout << "General Error: " << e.what() << "\n";
		rval = -1;
	}

	if(pConsumer) {
		pConsumer->close();
		delete pConsumer;
	}

	RdKafka::wait_destroyed(5000);

	std::cout << "Finished.\n";
	return rval;
}

