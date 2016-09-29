#-------------------------------------------------------------------------------
# COMPILE HELPERS
#
# \sa [Warning Level](
#        http://msdn.microsoft.com/library/thxezb7y.aspx)
#-------------------------------------------------------------------------------
# \author zhengrr
# \date 2016-8-4 – 9-28
# \copyright The MIT License
#-------------------------------------------------------------------------------

#-----------------------------------------------------------
# \since 2016-8-4
#-----------------------------------------------------------
option(C_HIGHEST_WARNING_LEVEL
       "Enable highest warning level for C." ON)
if(ENABLE_C_HIGHEST_WARNING_LEVEL)
   if(MSVC)
      if(CMAKE_C_FLAGS MATCHES "/Wall")
         # skip
      elseif(CMAKE_C_FLAGS MATCHES "/W[0-4]")
         string(REGEX REPLACE "/W[0-4]" "/Wall" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
      else()
         string(CONCAT CMAKE_C_FLAGS ${CMAKE_C_FLAGS} " /Wall ")
      endif()
   endif()
endif()

#-----------------------------------------------------------
# \brief Unicode Support
# \since 2016-8-4
#-----------------------------------------------------------
macro(unicode_support)
   if(WIN32)
      add_definitions("-DUNICODE" "-D_UNICODE")
   endif()
endmacro()
