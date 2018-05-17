
PROJECT(curl_spike)

SET(curl_spike_SRCS
        curl_spike.cpp
)
ADD_EXECUTABLE(curl_spike
        ${curl_spike_SRCS}
)

TARGET_LINK_LIBRARIES(curl_spike
	curl
)

INSTALL(PROGRAMS ${PROJECT_BINARY_DIR}/curl_spike
	DESTINATION /usr/bin
)
	
