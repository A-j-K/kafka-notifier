

CMAKE_MINIMUM_REQUIRED(VERSION 3.9)

PROJECT("test-kafka-lib")

ENABLE_TESTING()
FIND_PACKAGE(GTest REQUIRED)
FIND_PACKAGE(GMock REQUIRED)

INCLUDE_DIRECTORIES(
	"${GTEST_INCLUDE_DIRS}"
	"${GMOCK_INCLUDE_DIRS}"
	"${PROJECT_SOURCE_DIR}/lib"
	"${PROJECT_SOURCE_DIR}/test"
)

SET(test_SRCS
	test-jsonconfig.cpp
	test-kafka-conf.cpp
	test-kafka-event-cb.cpp
	test-kafka-consume-cb.cpp
	test-hexdump.cpp
)

ADD_EXECUTABLE(${PROJECT_NAME}
	${test_SRCS}
)

TARGET_LINK_LIBRARIES(${PROJECT_NAME}
	kafka_notifier_lib
	pthread
	${GTEST_LIBRARIES}
	${GTEST_MAIN_LIBRARIES}
	${GMOCK_LIBRARIES}
)

ADD_TEST(
	NAME "test-jsonconfig"
	COMMAND $<TARGET_FILE:${PROJECT_NAME}>
)

ADD_TEST(
	NAME "test-kafka-configure"
	COMMAND $<TARGET_FILE:${PROJECT_NAME}>
)

ADD_TEST(
	NAME "test-kafka-event-cb"
	COMMAND $<TARGET_FILE:${PROJECT_NAME}>
)

ADD_TEST(
	NAME "test-kafka-consume-cb"
	COMMAND $<TARGET_FILE:${PROJECT_NAME}>
)

