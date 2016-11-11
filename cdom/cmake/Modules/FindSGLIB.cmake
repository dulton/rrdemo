# zhengrr
# 2016-11-11
# The MIT License

#[======================================================================[.rst:
FindSGLIB
---------

Find SGLIB.

::

  SGLIB_FOUND
  SGLIB_ROOT_DIR
  SGLIB_INCLUDE_DIRS

#]======================================================================]
function(find_sglib)
  set(SGLIB_FOUND TRUE)

  # check validity
  if(NOT IS_DIRECTORY "${SGLIB_ROOT_DIR}")
    set(SGLIB_FOUND FALSE)
  endif()

  # check effectivity & find results
  if(SGLIB_FOUND)
    find_path(SGLIB_INCLUDE_DIRS
      NAMES "sglib/sglib.h"
      PATHS "${SGLIB_ROOT_DIR}/include")
  endif()

  # result variables
  include(FindPackageHandleStandardArgs)
  find_package_handle_standard_args(SGLIB
    FOUND_VAR SGLIB_FOUND
    REQUIRED_VARS SGLIB_INCLUDE_DIRS)

  set(SGLIB_FOUND ${SGLIB_FOUND} PARENT_SCOPE)
  set(SGLIB_ROOT_DIR ${SGLIB_ROOT_DIR} CACHE PATH "SGLIB root directory.")
  mark_as_advanced(SGLIB_INCLUDE_DIRS)
endfunction()

find_sglib()
