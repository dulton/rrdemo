#==============================================================================#
# \file                                                                        #
# \brief RrDemo Supports Helpers                                               #
# \author zhengrr                                                              #
# \date 2016-10-8 – 10-9                                                       #
# \copyright The MIT License                                                   #
#==============================================================================#
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)
cmake_policy(SET CMP0057 NEW)  # CMake 3.3+

#------------------------------------------------------------------------------#
# \brief Enable Highest Warning Level Support                                  #
# \sa [Warning Level](http://msdn.microsoft.com/library/thxezb7y.aspx)         #
# \since 2016-9-30 – 10-8                                                      #
#------------------------------------------------------------------------------#
function(rrdemo_enable_highest_warning_level_support)
   get_property(langs GLOBAL PROPERTY ENABLED_LANGUAGES)

   if("C" IN_LIST langs)
      if(MSVC)
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
      if(MSVC)
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

#------------------------------------------------------------------------------#
# \brief Enable Unicode Support                                                #
# \since 2016-9-30 – 10-8                                                      #
#------------------------------------------------------------------------------#
function(rrdemo_enable_unicode_support)
   if(MSVC)
      add_definitions("-DUNICODE" "-D_UNICODE")
   endif()
endfunction()

#------------------------------------------------------------------------------#
# \brief Find QTDIR                                                            #
# \since 2016-10-3 – 10-8                                                      #
#------------------------------------------------------------------------------#
function(rrdemo_find_qtdir)
   math(EXPR addw "8 * ${CMAKE_SIZEOF_VOID_P}")

   if(DEFINED QTDIR${addw})
      set(QTDIR "${QTDIR${addw}}")
   elseif(DEFINED QTDIR)
      # skip
   elseif(DEFINED ENV{QTDIR${addw}})
      set(QTDIR "$ENV{QTDIR${addw}}")
   elseif(DEFINED ENV{QTDIR})
      set(QTDIR "$ENV{QTDIR}")
   else()
      message(FATAL_ERROR "'QTDIR' cannot be found.")
   endif()

   list(APPEND CMAKE_PREFIX_PATH "${QTDIR}")

   set(QTDIR ${QTDIR} PARENT_SCOPE)
   set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} PARENT_SCOPE)
endfunction()
