#  GMOCK_FOUND - system has Jansson
#  GMOCK_INCLUDE_DIRS - the Jansson include directory
#  GMOCK_LIBRARIES - Link these to use Jansson

if (GMOCK_LIBRARIES AND GMOCK_INCLUDE_DIRS)
  # in cache already
  set(GMOCK_FOUND TRUE)
else (GMOCK_LIBRARIES AND GMOCK_INCLUDE_DIRS)
  find_path(GMOCK_INCLUDE_DIR
    NAMES
      gmock.h
    PATHS
      /usr/include
      /usr/include/gmock
      /usr/local/include
      /usr/local/include/gmock
      /opt/local/include
      /sw/include
  )

find_library(GMOCK_LIBRARY
    NAMES
      gmock
    PATHS
      /usr/lib
      /usr/local/lib
      /opt/local/lib
      /sw/lib
  )

set(GMOCK_INCLUDE_DIRS
  ${GMOCK_INCLUDE_DIR}
  )

if (GMOCK_LIBRARY)
  set(GMOCK_LIBRARIES
    ${GMOCK_LIBRARIES}
    ${GMOCK_LIBRARY}
    )
endif (GMOCK_LIBRARY)

  include(FindPackageHandleStandardArgs)
  find_package_handle_standard_args(GMock DEFAULT_MSG
    GMOCK_LIBRARIES GMOCK_INCLUDE_DIRS)

  # show the GMOCK_INCLUDE_DIRS and GMOCK_LIBRARIES variables only in the advanced view
  mark_as_advanced(GMOCK_INCLUDE_DIRS GMOCK_LIBRARIES)

endif (GMOCK_LIBRARIES AND GMOCK_INCLUDE_DIRS)


