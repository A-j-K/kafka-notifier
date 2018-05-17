#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// https://github.com/edenhill/librdkafka/blob/master/src-cpp/rdkafkacpp.h
#include <librdkafka/rdkafkacpp.h>

class MockRdKafkaTopic : public RdKafka::Topic
{
public:
	MOCK_CONST_METHOD0(name, const std::string());
	MOCK_CONST_METHOD1(partition_available, bool(int32_t));
	MOCK_CONST_METHOD2(offset_store, RdKafka::ErrorCode(int32_t, int64_t));
};

class MockRdKafkaMessage : public RdKafka::Message
{
public:
	MOCK_CONST_METHOD0(errstr, std::string());	
	MOCK_CONST_METHOD0(err, RdKafka::ErrorCode());
	MOCK_CONST_METHOD0(topic, RdKafka::Topic*());
	MOCK_CONST_METHOD0(topic_name, std::string());
	MOCK_CONST_METHOD0(partition, int32_t());
	MOCK_CONST_METHOD0(payload, void*());
	MOCK_CONST_METHOD0(len, size_t());
	MOCK_CONST_METHOD0(key, const std::string*());
	MOCK_CONST_METHOD0(key_pointer, const void*());
	MOCK_CONST_METHOD0(key_len, size_t());
	MOCK_CONST_METHOD0(offset, int64_t());
	MOCK_CONST_METHOD0(latency, int64_t());
	MOCK_CONST_METHOD0(timestamp, RdKafka::MessageTimestamp());
	MOCK_CONST_METHOD0(msg_opaque, void*());
};

class MockRdKafkaKafkaConsumer : public RdKafka::KafkaConsumer
{
public:
	MOCK_METHOD1(assignment, RdKafka::ErrorCode(std::vector<RdKafka::TopicPartition*>&));
	MOCK_METHOD1(subscription, RdKafka::ErrorCode(std::vector<std::string>&));
	MOCK_METHOD1(subscribe, RdKafka::ErrorCode(const std::vector<std::string>&));
	MOCK_METHOD0(unsubscribe, RdKafka::ErrorCode());
	MOCK_METHOD1(assign, RdKafka::ErrorCode(const std::vector<RdKafka::TopicPartition*>&));
	MOCK_METHOD0(unassign, RdKafka::ErrorCode());
	MOCK_METHOD1(consume, RdKafka::Message*(int));
	MOCK_METHOD0(commitSync, RdKafka::ErrorCode());
	MOCK_METHOD0(commitAsync, RdKafka::ErrorCode());
	MOCK_METHOD1(commitSync, RdKafka::ErrorCode(RdKafka::Message*));
	MOCK_METHOD1(commitAsync, RdKafka::ErrorCode(RdKafka::Message*));
	MOCK_METHOD1(commitSync, RdKafka::ErrorCode(std::vector<RdKafka::TopicPartition*>&));
	MOCK_METHOD1(commitAsync, RdKafka::ErrorCode(const std::vector<RdKafka::TopicPartition*>&));
	MOCK_METHOD2(committed, RdKafka::ErrorCode(std::vector<RdKafka::TopicPartition*>&, int));
	MOCK_METHOD1(position, RdKafka::ErrorCode(std::vector<RdKafka::TopicPartition*>&));
	MOCK_METHOD0(close, RdKafka::ErrorCode());
	MOCK_METHOD2(seek, RdKafka::ErrorCode(const RdKafka::TopicPartition&, int));
	MOCK_METHOD1(offset_store, RdKafka::ErrorCode(std::vector<RdKafka::TopicPartition*>&));
};

class MockRdKafkaConsumer : public RdKafka::Consumer
{
public:
	MOCK_METHOD4(start, RdKafka::ErrorCode(RdKafka::Topic*,int32_t,int64_t,RdKafka::Queue*));
	MOCK_METHOD2(stop, RdKafka::ErrorCode(RdKafka::Topic*,int32_t));
	MOCK_METHOD4(seek, RdKafka::ErrorCode(RdKafka::Topic*,int32_t,int64_t,RdKafka::Queue*));
	MOCK_METHOD3(consume, RdKafka::Message*(RdKafka::Topic*,int32_t,int));
	MOCK_METHOD2(consume, RdKafka::Message*(RdKafka::Queue*,int));
	MOCK_METHOD5(consume_callback, int(RdKafka::Topic*,int32_t,int,RdKafka::ConsumeCb*,void*));
	MOCK_METHOD4(consume_callback, int(RdKafka::Queue*,int,RdKafka::ConsumeCb*,void*));
};

class MockRdKafkaProducer : public RdKafka::Producer
{
public:
	MOCK_METHOD7(produce, RdKafka::ErrorCode(RdKafka::Topic*,int32_t,int,void*,size_t,std::string*,void*));
	MOCK_METHOD8(produce, RdKafka::ErrorCode(RdKafka::Topic*,int32_t,int,void*,size_t,const void*,size_t,void*));
	MOCK_METHOD9(produce, RdKafka::ErrorCode(const std::string,int32_t,int,void*,size_t,const void*,size_t,int64_t,void*));
	MOCK_METHOD5(produce, RdKafka::ErrorCode(RdKafka::Topic*,int32_t,const std::vector<char>,const std::vector<char>,void*));
	MOCK_METHOD1(flush, RdKafka::ErrorCode(int));
};

class MockRdKafkaBrokerMetadata : public RdKafka::BrokerMetadata
{
public:
	MOCK_CONST_METHOD0(id, int32_t());
	MOCK_CONST_METHOD0(host, const std::string());
	MOCK_CONST_METHOD0(port, int());
};

class MockRdKafkaPartitionMetadata : public RdKafka::PartitionMetadata
{
public:
	MOCK_CONST_METHOD0(id, int32_t());
	MOCK_CONST_METHOD0(err, RdKafka::ErrorCode());
	MOCK_CONST_METHOD0(leader, int32_t());
	MOCK_CONST_METHOD0(replicas, const std::vector<int32_t>*());
	MOCK_CONST_METHOD0(isrs, const std::vector<int32_t>*());
};

class MockRdKafkaTopicPartition : public RdKafka::TopicPartition
{
public:
	MOCK_METHOD0(partition, int());
	MOCK_METHOD0(offset, int64_t());
	MOCK_METHOD1(set_offset, void(int64_t));
	MOCK_CONST_METHOD0(topic, const std::string&());
	MOCK_CONST_METHOD0(err, RdKafka::ErrorCode());
};

class MockRdKafkaTopicMetadata : public RdKafka::TopicMetadata
{
public:
	MOCK_CONST_METHOD0(topic, const std::string());
	MOCK_CONST_METHOD0(partitions, const RdKafka::TopicMetadata::PartitionMetadataVector*());
	MOCK_CONST_METHOD0(err, RdKafka::ErrorCode());
};

class MockRdKafkaMetadata : public RdKafka::Metadata
{
public:
	MOCK_CONST_METHOD0(brokers, const RdKafka::Metadata::BrokerMetadataVector*());
	MOCK_CONST_METHOD0(topics, const RdKafka::Metadata::TopicMetadataVector*());
	MOCK_CONST_METHOD0(orig_broker_id, int32_t());
	MOCK_CONST_METHOD0(orig_broker_name, const std::string());
};

class MockRdKafkaConsumeCb : public RdKafka::ConsumeCb
{
public:
	MOCK_METHOD2(consume_cb, void(RdKafka::Message&,void*));
};

class MockRdKafkaEvent : public RdKafka::Event
{
public:
	MOCK_CONST_METHOD0(type, RdKafka::Event::Type());
	MOCK_CONST_METHOD0(err, RdKafka::ErrorCode());
	MOCK_CONST_METHOD0(severity, RdKafka::Event::Severity());
	MOCK_CONST_METHOD0(fac, std::string());
	MOCK_CONST_METHOD0(str, std::string());
	MOCK_CONST_METHOD0(throttle_time, int());
	MOCK_CONST_METHOD0(broker_name, std::string());
	MOCK_CONST_METHOD0(broker_id, int());
};

class MockRdKafkaEventCb : public RdKafka::EventCb
{
public:
	MOCK_METHOD1(event_cb, void(RdKafka::Event&));
};

class MockRdKafkaConf : public RdKafka::Conf
{
public:
	MOCK_METHOD3(set, RdKafka::Conf::ConfResult(const std::string&,RdKafka::Conf*,std::string&));
	MOCK_METHOD3(set, RdKafka::Conf::ConfResult(const std::string&,const RdKafka::Conf*,std::string&));
	MOCK_METHOD3(set, RdKafka::Conf::ConfResult(const std::string&,const std::string &,std::string &));
	MOCK_METHOD3(set, RdKafka::Conf::ConfResult(const std::string&,RdKafka::DeliveryReportCb*,std::string&));
	MOCK_METHOD3(set, RdKafka::Conf::ConfResult(const std::string&,RdKafka::EventCb*,std::string&));
	MOCK_METHOD3(set, RdKafka::Conf::ConfResult(const std::string&,RdKafka::PartitionerCb*,std::string&));
	MOCK_METHOD3(set, RdKafka::Conf::ConfResult(const std::string&,RdKafka::PartitionerKeyPointerCb*,std::string&));
	MOCK_METHOD3(set, RdKafka::Conf::ConfResult(const std::string&,RdKafka::SocketCb*,std::string&));
	MOCK_METHOD3(set, RdKafka::Conf::ConfResult(const std::string&,RdKafka::OpenCb*,std::string&));
	MOCK_METHOD3(set, RdKafka::Conf::ConfResult(const std::string&,RdKafka::RebalanceCb*,std::string&));
	MOCK_METHOD3(set, RdKafka::Conf::ConfResult(const std::string&,RdKafka::OffsetCommitCb*,std::string&));
	MOCK_METHOD3(set, RdKafka::Conf::ConfResult(const std::string&,RdKafka::ConsumeCb*,std::string&));
	MOCK_CONST_METHOD2(get,RdKafka::Conf::ConfResult(const std::string&,std::string&));
	MOCK_CONST_METHOD1(get,RdKafka::Conf::ConfResult(RdKafka::DeliveryReportCb*&));
	MOCK_CONST_METHOD1(get,RdKafka::Conf::ConfResult(RdKafka::EventCb*&));
	MOCK_CONST_METHOD1(get,RdKafka::Conf::ConfResult(RdKafka::PartitionerCb*&));
	MOCK_CONST_METHOD1(get,RdKafka::Conf::ConfResult(RdKafka::PartitionerKeyPointerCb*&));
	MOCK_CONST_METHOD1(get,RdKafka::Conf::ConfResult(RdKafka::SocketCb*&));
	MOCK_CONST_METHOD1(get,RdKafka::Conf::ConfResult(RdKafka::OpenCb*&));
	MOCK_CONST_METHOD1(get,RdKafka::Conf::ConfResult(RdKafka::RebalanceCb*&));
	MOCK_CONST_METHOD1(get,RdKafka::Conf::ConfResult(RdKafka::OffsetCommitCb*&));
	MOCK_METHOD0(dump, std::list<std::string>*());
};


