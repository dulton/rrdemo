#==============================================================================#
# \file
# \brief Append QTDIR to Prefix
# \author zhengrr
# \date 2016-10-18
# \copyright The MIT License
#==============================================================================#
function(append_qtdir_to_prefix)
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

append_qtdir_to_prefix()
