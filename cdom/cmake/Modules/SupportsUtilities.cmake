# zhengrr
# 2016-10-8 – 28
# The MIT License

#[======================================================================[.rst:
Supports Utilities
------------------

Defines some options sets for compiler, linker, etc..

CMake 3.3+ required.
#]======================================================================]
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)
cmake_policy(SET CMP0057 NEW)  # CMake 3.3+

#[==================================================[.rst:
.. command:: enable_highest_warning_level_support

  ::

    enable_highest_warning_level_support()

  Example usage:

  ::

    # Product(Root) CMakeLists.txt
    project...
    ...
    enable_highest_warning_level_support()
    ...
    add_subdirectory...

  See also:

  - `GCC Warning Options
    <http://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html>`_
  - `VC++ Warning Level
    <http://msdn.microsoft.com/library/thxezb7y.aspx>`_
#]==================================================]
function(enable_highest_warning_level_support)
  get_property(langs GLOBAL PROPERTY ENABLED_LANGUAGES)

  if("C" IN_LIST langs)
    if(CMAKE_COMPILER_IS_GNUCC)
      string(CONCAT CMAKE_C_FLAGS "${CMAKE_C_FLAGS}" " -Wall ")
    elseif(MSVC)
      if(CMAKE_C_FLAGS MATCHES "/Wall")
        # skip
      elseif(CMAKE_C_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/Wall" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
      else()
        string(CONCAT CMAKE_C_FLAGS "${CMAKE_C_FLAGS}" " /Wall ")
      endif()
    endif()
    set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} PARENT_SCOPE)
  endif()

  if("CXX" IN_LIST langs)
    if(CMAKE_COMPILER_IS_GNUCXX)
      string(CONCAT CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" " -Wall ")
    elseif(MSVC)
      if(CMAKE_CXX_FLAGS MATCHES "/Wall")
        # skip
      elseif(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/Wall" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
      else()
        string(CONCAT CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" " /Wall ")
      endif()
    endif()
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} PARENT_SCOPE)
  endif()
endfunction()

#[==================================================[.rst:
.. command:: enable_unicode_support

  ::

    enable_unicode_support()

  Example usage:

  ::

    # Project(Sub) CMakeLists.txt
    project...
    ...
    enable_unicode_support()
    ...
    add_executable...
    add_library...

#]==================================================]
function(enable_unicode_support)
  if(MSVC)
    add_definitions("-DUNICODE" "-D_UNICODE")
  endif()
endfunction()
