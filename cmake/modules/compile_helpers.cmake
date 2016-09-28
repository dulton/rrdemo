#-------------------------------------------------------------------------------
# COMPILE HELPERS
#
# \sa [Warning Level](
#    http://msdn.microsoft.com/library/thxezb7y.aspx)
#-------------------------------------------------------------------------------
# \author zhengrr
# \date 2016-8-4 – 9-28
# \copyright The MIT License
#-------------------------------------------------------------------------------

#-----------------------------------------------------------
# \brief C HIGHEST WARNING LEVEL
# \since 2016-8-4
#-----------------------------------------------------------
option(ENABLE_C_HIGHEST_WARNING_LEVEL
   "Enable C highest warning level." ON)
if(ENABLE_C_HIGHEST_WARNING_LEVEL)
   
   if(MSVC)
      if(CMAKE_C_FLAGS MATCHES "/Wall")
         # skip
      elseif(CMAKE_C_FLAGS MATCHES "/W[0-4]")
         string(REGEX REPLACE "/W[0-4]" "/Wall"
                CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
      else()
         string(CONCAT CMAKE_C_FLAGS ${CMAKE_C_FLAGS}
                " /Wall ")
      endif()
   endif()
endif()
