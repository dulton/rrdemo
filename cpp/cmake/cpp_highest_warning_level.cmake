#-------------------------------------------------------------------------------
# CPP HIGHEST WARNING LEVEL
#
# \sa [CMAKE_<LANG>_FLAGS — CMake 3.6.1 Documentation]{
#    http://cmake.org/cmake/help/v3.6/variable/CMAKE_LANG_FLAGS.html}
# \sa [Warning Level](
#    http://msdn.microsoft.com/library/thxezb7y.aspx)
#-------------------------------------------------------------------------------
# \author zhengrr
# \date 2016-8-4
# \copyright The MIT License
#-------------------------------------------------------------------------------
option(ENABLE_CPP_HIGHEST_WARNING_LEVEL
   "Enable CPP highest warning level." ON)
if(ENABLE_CPP_HIGHEST_WARNING_LEVEL)
   
   if(MSVC)
      if(CMAKE_CXX_FLAGS MATCHES "/Wall")
         # skip
      elseif(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
         string(REGEX REPLACE "/W[0-4]" "/Wall"
                CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
      else()
         string(CONCAT CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS}
                " /Wall ")
      endif()
   endif()
   
endif()
