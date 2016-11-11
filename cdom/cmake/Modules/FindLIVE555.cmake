# zhengrr
# 2016-10-24 – 11-11
# The MIT License

#[======================================================================[.rst:
FindLIVE555
-----------

Find LIVE555.

::

  LIVE555_FOUND
  LIVE555_LIBRARIES
  LIVE555_ROOT_DIR
  LIVE555_INCLUDE_DIRS

::

  LIVE555_BasicUsageEnvironment_LIBRARY
  LIVE555_groupsock_LIBRARY
  LIVE555_liveMedia_LIBRARY
  LIVE555_UsageEnvironment_LIBRARY

#]======================================================================]
function(find_live555)
  set(LIVE555_FOUND TRUE)

  # check validity
  if(NOT IS_DIRECTORY "${LIVE555_ROOT_DIR}")
    set(LIVE555_FOUND FALSE)
  endif()

  # check effectivity & find results
  if(LIVE555_FOUND)
    find_path(LIVE555_INCLUDE_DIRS
      NAMES
      "live555/BasicUsageEnvironment.hh"
      "live555/Groupsock.hh"
      "live555/liveMedia.hh"
      "live555/UsageEnvironment.hh"
      PATHS
      "${LIVE555_ROOT_DIR}/include")
    find_library(LIVE555_BasicUsageEnvironment_LIBRARY
      NAMES "BasicUsageEnvironment" PATHS "${LIVE555_ROOT_DIR}/lib")
    find_library(LIVE555_groupsock_LIBRARY
      NAMES "groupsock" PATHS "${LIVE555_ROOT_DIR}/lib")
    find_library(LIVE555_liveMedia_LIBRARY
      NAMES "liveMedia" PATHS "${LIVE555_ROOT_DIR}/lib")
    find_library(LIVE555_UsageEnvironment_LIBRARY
      NAMES "UsageEnvironment" PATHS "${LIVE555_ROOT_DIR}/lib")
  endif()

  # result variables
  include(FindPackageHandleStandardArgs)
  find_package_handle_standard_args(LIVE555
    FOUND_VAR LIVE555_FOUND
    REQUIRED_VARS LIVE555_INCLUDE_DIRS
    LIVE555_BasicUsageEnvironment_LIBRARY
    LIVE555_groupsock_LIBRARY
    LIVE555_liveMedia_LIBRARY
    LIVE555_UsageEnvironment_LIBRARY)

  set(LIVE555_LIBRARIES
    ${LIVE555_BasicUsageEnvironment_LIBRARY}
    ${LIVE555_groupsock_LIBRARY}
    ${LIVE555_liveMedia_LIBRARY}
    ${LIVE555_UsageEnvironment_LIBRARY})

  set(LIVE555_FOUND ${LIVE555_FOUND} PARENT_SCOPE)
  set(LIVE555_ROOT_DIR ${LIVE555_ROOT_DIR} CACHE PATH "LIVE555 root directory.")
  set(LIVE555_LIBRARIES ${LIVE555_LIBRARIES} PARENT_SCOPE)
  mark_as_advanced(LIVE555_INCLUDE_DIRS
    LIVE555_BasicUsageEnvironment_LIBRARY
    LIVE555_groupsock_LIBRARY
    LIVE555_liveMedia_LIBRARY
    LIVE555_UsageEnvironment_LIBRARY)
endfunction()

find_live555()
