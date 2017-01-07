# zhengrr
# 2016-10-21 – 2017-1-7
# The MIT License

#[======================================================================[.rst:
FindQt5CMake
------------

Find Qt5 CMake modules.

CMake 3.3+ required.

::

  QT5CMAKE_FOUND
  QT5CMAKE_ROOT_DIR
#]======================================================================]
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)
cmake_policy(SET CMP0057 NEW)  # CMake 3.3+

function(find_qt5_cmake)
  set(QT5CMAKE_FOUND TRUE)

  # default value & check validity
  if(NOT QT5CMAKE_ROOT_DIR)
    math(EXPR addw "8 * ${CMAKE_SIZEOF_VOID_P}")
    if(DEFINED QTDIR${addw})
      set(QT5CMAKE_ROOT_DIR "${QTDIR${addw}}")
    elseif(DEFINED ENV{QTDIR${addw}})
      set(QT5CMAKE_ROOT_DIR "$ENV{QTDIR${addw}}")
    elseif(DEFINED ENV{QTDIR})
      set(QT5CMAKE_ROOT_DIR "$ENV{QTDIR}")
    else()
      set(QT5CMAKE_FOUND FALSE)
    endif()
  elseif(NOT IS_DIRECTORY "${QT5CMAKE_ROOT_DIR}")
    set(QT5CMAKE_FOUND FALSE)
  endif()

  # check effectivity & find results
  if(QT5CMAKE_FOUND)
    find_path(QT5CMAKE_LIBRARIES
      NAMES "Qt5/Qt5Config.cmake"
      PATHS "${QT5CMAKE_ROOT_DIR}/lib/cmake")
  endif()

  # result variables
  include(FindPackageHandleStandardArgs)
  find_package_handle_standard_args(Qt5CMake
    FOUND_VAR QT5CMAKE_FOUND
    REQUIRED_VARS QT5CMAKE_LIBRARIES)

  set(QT5CMAKE_FOUND ${QT5CMAKE_FOUND} PARENT_SCOPE)
  set(QT5CMAKE_ROOT_DIR ${QT5CMAKE_ROOT_DIR} CACHE PATH "Qt5CMake root directory.")
  mark_as_advanced(QT5CMAKE_LIBRARIES)

  if(QT5CMAKE_FOUND)
    if(NOT QT5CMAKE_ROOT_DIR IN_LIST CMAKE_PREFIX_PATH)
      list(APPEND CMAKE_PREFIX_PATH "${QT5CMAKE_ROOT_DIR}")
      set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} PARENT_SCOPE)
    endif()
  endif()
endfunction()

find_qt5_cmake()
