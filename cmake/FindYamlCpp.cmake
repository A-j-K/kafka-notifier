
# Defines:-
#
# YAMLCPP_INCLUDE_DIR
# YAMLCPP_LIBS_DIR
# YAMLCPP_LIBS
#

IF(NOT EXISTS "/usr/local/include/yaml-cpp/yaml.h")
    MESSAGE(FATAL_ERROR "Failed to find /usr/local/include/yaml-cpp.h")
ELSE()
	MESSAGE(STATUS "YAML-CPP found")
	SET(YAMLCPP_FOUND 1)
	SET(YAMLCPP_INCLUDE_DIR "/usr/local/include")
	SET(YAMLCPP_LIBS_DIR "/usr/local/lib")
	SET(YAMLCPP_LIBS
		/usr/local/lib/libyaml-cpp.so
	)
ENDIF()


