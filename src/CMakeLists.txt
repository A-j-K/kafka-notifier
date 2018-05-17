
INCLUDE_DIRECTORIES(
	"${PROJECT_SOURCE_DIR}/src"
)

SET(notifier_SRCS
	kafka_conf.cpp
	kafka_event_cb.cpp
	kafka_consume_cb.cpp
	curler.cpp
	curlerc.cpp
	wcurl.cpp
	gkw_consume_cb.cpp
	event_cb.cpp
	hexdump.cpp
	abstract_config.cpp
	json_config.cpp
	config_factory.cpp
)

ADD_LIBRARY(kafka_notifier_lib
	${notifier_SRCS}
)

TARGET_LINK_LIBRARIES(kafka_notifier_lib
	curl
	rdkafka
	rdkafka++
	pthread
	jansson
)

