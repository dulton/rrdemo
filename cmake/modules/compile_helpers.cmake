#-------------------------------------------------------------------------------
# COMPILE HELPERS
#-------------------------------------------------------------------------------
# \author zhengrr
# \date 2016-8-4 – 9-29
# \copyright The MIT License
#-------------------------------------------------------------------------------

#-----------------------------------------------------------
# \brief Enable Highest Warning Level Support
# \sa [Warning Level](
#        http://msdn.microsoft.com/library/thxezb7y.aspx)
# \since 2016-8-4
#-----------------------------------------------------------
function(ena_highest_wlvl_spt)
   if(CMAKE_C_FLAGS)
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

   if(CMAKE_CXX_FLAGS)
      # TODO
   endif()
endfunction()

#-----------------------------------------------------------
# \brief Enable Unicode Support
# \since 2016-8-4
#-----------------------------------------------------------
function(ena_unicode_spt)
   if(WIN32)
      add_definitions("-DUNICODE" "-D_UNICODE")
   endif()
endfunction()
