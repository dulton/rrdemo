#-------------------------------------------------------------------------------
# APPEND QTDIR TO PREFIXES
#-------------------------------------------------------------------------------
# \author zhengrr
# \date 2016-8-4
# \copyright The MIT License
#-------------------------------------------------------------------------------
option(ENABLE_APPEND_QTDIR_TO_PREFIXES
   "Enable highest warning level." ON)
if(ENABLE_APPEND_QTDIR_TO_PREFIXES)
   
   math(EXPR addrw "8 * ${CMAKE_SIZEOF_VOID_P}")
   
   if(DEFINED QTDIR${addrw})
      set(QTDIR "${QTDIR${addrw}}")
   elseif(DEFINED QTDIR)
      # skip
   elseif(DEFINED ENV{QTDIR${addrw}})
      set(QTDIR "$ENV{QTDIR${addrw}}")
   elseif(DEFINED ENV{QTDIR})
      set(QTDIR "$ENV{QTDIR}")
   else()
      message(FATAL_ERROR "'QTDIR' cannot be found.")
   endif()
   
   list(APPEND CMAKE_PREFIX_PATH "${QTDIR}")
   
endif()