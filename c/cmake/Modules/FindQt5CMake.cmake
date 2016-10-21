# zhengrr
# 2016-10-21
# The MIT License

#[======================================================================[.rst:
FindQt5CMake
------------

Find Qt5 cmake modules.

CMake 3.3+ required.

::

  QT5CMAKE_FOUND
  QT5CMAKE_ROOT_DIR

#]======================================================================]
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)
cmake_policy(SET CMP0057 NEW)  # CMake 3.3+

function(find_qt5_cmake)
  set(QT5CMAKE_FOUND TRUE)

  # check validity
  if(NOT QT5CMAKE_ROOT_DIR)
    # else if auto-find QT5CMAKE_ROOT_DIR
    set(newauto TRUE)
    math(EXPR addw "8 * ${CMAKE_SIZEOF_VOID_P}")
    if(DEFINED QTDIR${addw})
      set(QT5CMAKE_ROOT_DIR "${QTDIR${addw}}")
    elseif(DEFINED ENV{QTDIR${addw}})
      set(QT5CMAKE_ROOT_DIR "$ENV{QTDIR${addw}}")
    elseif(DEFINED ENV{QTDIR})
      set(QT5CMAKE_ROOT_DIR "$ENV{QTDIR}")
    else()
      set(QT5CMAKE_FOUND FALSE)
      if(NOT Qt5CMake_FIND_QUIETLY)
        message(WARNING "Failed to auto-find QT5CMAKE_ROOT_DIR.")
      endif()
    endif()
  elseif(NOT IS_DIRECTORY "${QT5CMAKE_ROOT_DIR}")
    # if specified QT5CMAKE_ROOT_DIR (and invalid)
    set(QT5CMAKE_FOUND FALSE)
    if(NOT Qt5CMake_FIND_QUIETLY)
      message(WARNING "The specified QT5CMAKE_ROOT_DIR is invalid: ${QT5CMAKE_ROOT_DIR}")
    endif()
  endif()

  #TODO: check effectivity

  # append QT5CMAKE_ROOT_DIR to CMAKE_PREFIX_PATH
  if(QT5CMAKE_FOUND AND NOT QT5CMAKE_ROOT_DIR IN_LIST CMAKE_PREFIX_PATH)
    if(newauto AND NOT Qt5CMake_FIND_QUIETLY)
      message(STATUS "Found Qt5CMake: ${QT5CMAKE_ROOT_DIR}\\lib\\cmake")
    endif()
    list(APPEND CMAKE_PREFIX_PATH "${QT5CMAKE_ROOT_DIR}")
    set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} PARENT_SCOPE)
  endif()

  # returned variables
  set(QT5CMAKE_FOUND ${QT5CMAKE_FOUND} PARENT_SCOPE)
  set(QT5CMAKE_ROOT_DIR ${QT5CMAKE_ROOT_DIR} PARENT_SCOPE)

  # check necessity
  if(NOT QT5CMAKE_FOUND AND Qt5CMake_FIND_REQUIRED)
    message(FATAL_ERROR "Failed to find Qt5 cmake modules.")
  endif()
endfunction()

find_qt5_cmake()
set(QT5CMAKE_ROOT_DIR ${QT5CMAKE_ROOT_DIR} CACHE PATH "Qt5CMake root directory.")
mark_as_advanced(QT5CMAKE_ROOT_DIR)
