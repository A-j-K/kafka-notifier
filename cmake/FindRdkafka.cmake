#  RDKAFKA_FOUND - system has Jansson
#  RDKAFKA_INCLUDE_DIRS - the Jansson include directory
#  RDKAFKA_LIBRARIES - Link these to use Jansson

if (RDKAFKA_LIBRARIES AND RDKAFKA_INCLUDE_DIRS)
  # in cache already
  set(RDKAFKA_FOUND TRUE)
else (RDKAFKA_LIBRARIES AND RDKAFKA_INCLUDE_DIRS)
  find_path(RDKAFKA_INCLUDE_DIR
    NAMES
      rdkafka.h
      rdkafkacpp.h
    PATHS
      /usr/include
      /usr/include/librdkafka
      /usr/local/include
      /usr/local/include/librdkafka
      /opt/local/include
      /sw/include
  )

find_library(RDKAFKA_LIBRARY
    NAMES
      rdkafka
      rdkafka++
    PATHS
      /usr/lib
      /usr/local/lib
      /opt/local/lib
      /sw/lib
  )

set(RDKAFKA_INCLUDE_DIRS
  ${RDKAFKA_INCLUDE_DIR}
  )

if (RDKAFKA_LIBRARY)
  set(RDKAFKA_LIBRARIES
    ${RDKAFKA_LIBRARIES}
    ${RDKAFKA_LIBRARY}
    )
endif (RDKAFKA_LIBRARY)

  include(FindPackageHandleStandardArgs)
  find_package_handle_standard_args(rdkafka DEFAULT_MSG
    RDKAFKA_LIBRARIES RDKAFKA_INCLUDE_DIRS)

  # show the RDKAFKA_INCLUDE_DIRS and RDKAFKA_LIBRARIES variables only in the advanced view
  mark_as_advanced(RDKAFKA_INCLUDE_DIRS RDKAFKA_LIBRARIES)

endif (RDKAFKA_LIBRARIES AND RDKAFKA_INCLUDE_DIRS)


