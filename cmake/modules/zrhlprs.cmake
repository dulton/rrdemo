#-------------------------------------------------------------------------------
# ZhengRr HeLPeRS
#-------------------------------------------------------------------------------
# \author zhengrr
# \date 2016-9-30
# \copyright The MIT License
#-------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)
cmake_policy(SET CMP0057 NEW)  # CMake 3.3+

#-----------------------------------------------------------
# \brief Enable Highest Warning Level Support
# \sa [Warning Level](
#        http://msdn.microsoft.com/library/thxezb7y.aspx)
# \since 2016-9-30
#-----------------------------------------------------------
function(zr_ena_highest_wlvl_spt)
   get_property(langs GLOBAL PROPERTY ENABLED_LANGUAGES)

   if("C" IN_LIST langs)
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

   if("CXX" IN_LIST langs)
      if(MSVC)
         if(CMAKE_CXX_FLAGS MATCHES "/Wall")
            # skip
         elseif(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
            string(REGEX REPLACE "/W[0-4]" "/Wall" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
         else()
            string(CONCAT CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} " /Wall ")
         endif()
      endif()
   endif()
endfunction()

#-----------------------------------------------------------
# \brief Enable Unicode Support
# \since 2016-9-30
#-----------------------------------------------------------
function(zr_ena_unicode_spt)
   if(WIN32)
      add_definitions("-DUNICODE" "-D_UNICODE")
   endif()
endfunction()

#-----------------------------------------------------------
# \brief Make Project Extra Variables
# \since 2016-9-30
#-----------------------------------------------------------
macro(zr_make_project_extvars)
   string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_UPPER)
   string(TOLOWER ${PROJECT_NAME} PROJECT_NAME_LOWER)
   set(PRJUPR ${PROJECT_NAME_UPPER})
   set(PRJLWR ${PROJECT_NAME_LOWER})
endmacro()

#-----------------------------------------------------------
# \brief Make Product Variables
# \since 2016-9-30
#-----------------------------------------------------------
macro(zr_make_product_vars)
   set(PRODUCT_NAME ${PROJECT_NAME})
   string(TOUPPER ${PROJECT_NAME} PRODUCT_NAME_UPPER)
   string(TOLOWER ${PROJECT_NAME} PRODUCT_NAME_LOWER)
   set(PRODUCT_SOURCE_DIR ${PROJECT_SOURCE_DIR})
   set(PRODUCT_BINARY_DIR ${PROJECT_BINARY_DIR})
   set(PRODUCT_VERSION ${PROJECT_VERSION})
   set(PRODUCT_VERSION_MAJRO ${PROJECT_VERSION_MAJOR})
   set(PRODUCT_VERSION_MINOR ${PROJECT_VERSION_MINOR})
   set(PRODUCT_VERSION_PATCH ${PROJECT_VERSION_PATCH})
   set(PRODUCT_VERSION_TWEAK ${PROJECT_VERSION_TWEAK})
endmacro()

#-----------------------------------------------------------
# \brief Get (& Group) Source
# \since 2016-9-30
#-----------------------------------------------------------
macro(zr_get_src)
   set(opts     # OPTIONS
       "RECURSE")  # [in] Enable recurse.
   set(ones     # ONE VALUE ARGS
       "SRCVAR"    # [out] Source variable, matchs regex.
       "SRCDIR"    # [in] Source directory, absolute path, need exist.
       "GRPNOM")   # [in] Group name, matchs regex.
   set(muts     # MULTI VALUE ARGS
       "SRCEXT")   # [in] Source extensions, matchs regex.
   cmake_parse_arguments("ZRFS" "${opts}" "${ones}" "${muts}" ${ARGN})

   if(ZRFS_RECURSE)
      set(ZRFS_RECURSE "_RECURSE")
   else()
      set(ZRFS_RECURSE "")
   endif()

   if((NOT ZRFS_SRCVAR) OR (NOT ZRFS_SRCVAR MATCHES "^[0-9A-Za-z_-]+$"))
      message(FATAL_ERROR "The argument SRCVAR was null or invalid, "
              "current input was '${ZRFS_SRCVAR}'.")
   endif()

   if((NOT ZRFS_SRCDIR) OR (NOT IS_DIRECTORY ${ZRFS_SRCDIR}))
      message(FATAL_ERROR "The argument SRCDIR was null or invalid, "
              "current input was '${ZRFS_SRCDIR}'.")
   endif()

   if((NOT ZRFS_GRPNOM) OR (NOT ZRFS_GRPNOM MATCHES "^[ 0-9A-Za-z/_-]+$"))
      message(FATAL_ERROR "The argument GRPNOM was null or invalid, "
              "current input was '${ZRFS_GRPNOM}'.")
   endif()

   if(NOT ZRFS_SRCEXT)
      message(FATAL_ERROR "The argument SRCEXT was null.")
   endif()
   foreach(ext ${ZRFS_SRCEXT})
      if(NOT ext MATCHES "^([.][0-9A-Za-z]+)+$")
         message(FATAL_ERROR "A argument in SRCEXT was invalid, "
                 "the argument was '${ext}' in '${ZRFS_SRCEXT}'.")
      endif()
   endforeach()

   unset(exts)
   foreach(ext ${ZRFS_SRCEXT})
      if(NOT ext IN_LIST exts)
         list(APPEND exts ${ext})
         file(GLOB${ZRFS_RECURSE} src "${ZRFS_SRCDIR}/*${ext}")
         foreach(file ${src})
            # get file
            if(NOT file IN_LIST ${ZRFS_SRCVAR})
               list(APPEND ${ZRFS_SRCVAR} ${file})
            endif()
            # group file
            get_filename_component(fdir ${file} DIRECTORY)
            string(REGEX REPLACE "^${ZRFS_SRCDIR}" "" freldir ${fdir})
            string(REPLACE "/" "\\\\" grpdir "${ZRFS_GRPNOM}${freldir}")
            source_group(${grpdir} FILES ${file})
         endforeach()
      endif()
   endforeach()
endmacro()

#-----------------------------------------------------------
# \brief Generate (& Get, Group) Source
# \since 2016-9-30
#-----------------------------------------------------------
macro(zr_gen_src)
   set(opts     # OPTIONS
       "RECURSE")  # [in] Enable recurse.
   set(ones     # ONE VALUE ARGS
       "SRCVAR"    # [out] Source variable, matchs regex.
       "SRCDIR"    # [in] Source directory, absolute path, need exist.
       "GENDIR"    # [in] Generated directory, absolute path.
       "GRPNOM")   # [in] Group name, matchs regex.
   set(muts     # MULTI VALUE ARGS
       "GENEXT")   # [in] Generating source extensions, matchs regex.
   cmake_parse_arguments("ZRGS" "${opts}" "${ones}" "${muts}" ${ARGN})

   if(ZRGS_RECURSE)
      set(ZRGS_RECURSE "_RECURSE")
   else()
      set(ZRGS_RECURSE "")
   endif()

   if((NOT ZRGS_SRCVAR) OR (NOT ZRGS_SRCVAR MATCHES "^[0-9A-Za-z_-]+$"))
      message(FATAL_ERROR "The argument SRCVAR was null or invalid, "
              "current input was '${ZRGS_SRCVAR}'.")
   endif()

   if((NOT ZRGS_SRCDIR) OR (NOT IS_DIRECTORY ${ZRGS_SRCDIR}))
      message(FATAL_ERROR "The argument SRCDIR was null or invalid, "
              "current input was '${ZRGS_SRCDIR}'.")
   endif()

   if((NOT ZRGS_GENDIR) OR (NOT IS_ABSOLUTE ${ZRGS_GENDIR}))
      message(FATAL_ERROR "The argument GENDIR was null or invalid, "
              "current input was '${ZRGS_GENDIR}'.")
   endif()

   if((NOT ZRGS_GRPNOM) OR (NOT ZRGS_GRPNOM MATCHES "^[ 0-9A-Za-z/_-]+$"))
      message(FATAL_ERROR "The argument GRPNOM was null or invalid, "
              "current input was '${ZRGS_GRPNOM}'.")
   endif()

   if(NOT ZRGS_GENEXT)
      message(FATAL_ERROR "The argument GENEXT was null.")
   endif()
   foreach(ext ${ZRGS_GENEXT})
      if(NOT ext MATCHES "^([.][0-9A-Za-z]+)+$")
         message(FATAL_ERROR "A argument in GENEXT was invalid, "
                 "the argument was '${ext}' in '${ZRGS_GENEXT}'.")
      endif()
   endforeach()

   unset(exts)
   foreach(ext ${ZRGS_GENEXT})
      if(NOT ext IN_LIST exts)
         list(APPEND exts ${ext})
         file(GLOB${ZRGS_RECURSE} src "${ZRGS_SRCDIR}/*${ext}")
         foreach(file ${src})
            # get file
            if(NOT file IN_LIST ${ZRGS_SRCVAR})
               list(APPEND ${ZRGS_SRCVAR} ${file})
            endif()
            # group file
            get_filename_component(fdir ${file} DIRECTORY)
            string(REGEX REPLACE "^${ZRGS_SRCDIR}" "" freldir ${fdir})
            string(REPLACE "/" "\\\\" grpdir "${ZRGS_GRPNOM}${freldir}")
            source_group(${grpdir} FILES ${file})
            # generate, get & group (generated) file
            get_filename_component(fnom ${file} NAME)
            string(REPLACE "." "\\." extrgx "${ext}")
            string(REGEX REPLACE "${extrgx}$" "" gnom ${fnom})
            set(gfile "${ZRGS_GENDIR}${freldir}/${gnom}")
            if(NOT gfile IN_LIST ${ZRGS_SRCVAR})
               configure_file(${file} ${gfile} @ONLY)
               list(APPEND ${ZRGS_SRCVAR} ${gfile})
               source_group(${grpdir} FILES ${gfile})
            endif()
         endforeach()
      endif()
   endforeach()
endmacro()

#-----------------------------------------------------------
# \brief Install Source
# \since 2016-9-30
#-----------------------------------------------------------
function(zr_ins_src)
   set(opts     # OPTIONS
       "RECURSE")  # [in] Enable recurse.
   set(ones     # ONE VALUE ARGS
       "SRCDIR"    # [in] Source directory, absolute path, need exist.
       "INSDIR")   # [in] Install directory, absolute path.
   set(muts     # MULTI VALUE ARGS
       "INSEXT")   # [in] Installing source extensions, matchs regex.
   cmake_parse_arguments("ZRIS" "${opts}" "${ones}" "${muts}" ${ARGN})

   if(ZRIS_RECURSE)
      set(ZRIS_RECURSE "_RECURSE")
   else()
      set(ZRIS_RECURSE "")
   endif()

   if((NOT ZRIS_SRCDIR) OR (NOT IS_DIRECTORY ${ZRIS_SRCDIR}))
      message(FATAL_ERROR "The argument SRCDIR was null or invalid, "
              "current input was '${ZRIS_SRCDIR}'.")
   endif()

   if((NOT ZRIS_INSDIR) OR (NOT IS_ABSOLUTE ${ZRIS_INSDIR}))
      message(FATAL_ERROR "The argument INSDIR was null or invalid, "
              "current input was '${ZRIS_INSDIR}'.")
   endif()

   if(NOT ZRIS_INSEXT)
      message(FATAL_ERROR "The argument INSEXT was null.")
   endif()
   foreach(ext ${ZRIS_INSEXT})
      if(NOT ext MATCHES "^([.][0-9A-Za-z]+)+$")
         message(FATAL_ERROR "A argument in INSEXT was invalid, "
                 "the argument was '${ext}' in '${ZRIS_INSEXT}'.")
      endif()
   endforeach()

   unset(exts)
   foreach(ext ${ZRIS_INSEXT})
      if(NOT ext IN_LIST exts)
         list(APPEND exts ${ext})
         file(GLOB${ZRIS_RECURSE} src "${ZRIS_SRCDIR}/*${ext}")
         foreach(file ${src})
            get_filename_component(fdir ${file} DIRECTORY)
            string(REGEX REPLACE "^${ZRIS_SRCDIR}" "" freldir ${fdir})
            install(FILES ${file} DESTINATION "${ZRIS_INSDIR}${freldir}")
         endforeach()
      endif()
   endforeach()
endfunction()

#-----------------------------------------------------------
# \brief Source Helper
# \since 2016-9-30
#-----------------------------------------------------------
macro(zr_srchlpr)
   set(opts     # OPTIONS
       "GENERATE"  # [in] Enable source generating.
       "INSTALL"   # [in] Enable source install.
       "RECURSE"   # [in] Enable recurse.
       "C"         # [in] Some extensions for C.
       "CPP")      # [in] Some extensions for C++.
   set(ones     # ONE VALUE ARGS
       "SRCVAR"    # [out] Source variable, matchs regex
       "SRCDIR"    # [in] Source directory, default current source directory.
       "GENDIR"    # [in] Generated directory, default current build directory.
       "INSDIR"    # [in] Install directory, default current install directory.
       "GRPNOM")   # [in] Group name, default current parent directory.
   set(muts     # MULTI VALUE ARGS
       "SRCEXT"    # [in] Source extensions, matchs regex.
       "GENEXT"    # [in] Generating source extensions, matchs regex.
       "INSEXT")   # [in] Installing source extensions, matchs regex.
   cmake_parse_arguments("ZRSH" "${opts}" "${ones}" "${muts}" ${ARGN})

   set(prj_src "${PROJECT_SOURCE_DIR}")
   set(cur_src "${CMAKE_CURRENT_LIST_DIR}")
   string(REGEX REPLACE "^${prj_src}" "" rel_dir "${cur_src}")
   set(prj_bin "${PROJECT_BINARY_DIR}")
   set(cur_bin "${prj_bin}${rel_dir}")
   string(TOLOWER "${PROJECT_NAME}" prj_low)
   set(prj_ins "${CMAKE_INSTALL_PREFIX}")
   set(cur_ins "${prj_ins}/include/${prj_low}")

   if(ZRSH_RECURSE)
      set(ZRSH_RECURSE "RECURSE")
   else()
      set(ZRSH_RECURSE "")
   endif()

   if((NOT ZRSH_SRCVAR) OR (NOT ZRSH_SRCVAR MATCHES "^[0-9A-Za-z_-]+$"))
      message(FATAL_ERROR "The argument SRCVAR was null or invalid, "
              "current input was '${ZRSH_SRCVAR}'.")
   endif()

   if(NOT ZRSH_SRCDIR)
      set(zrsh_srcdir "${cur_src}")
   else()
      set(zrsh_srcdir "${ZRSH_SRCDIR}")
      if(NOT IS_DIRECTORY "${zrsh_srcdir}")
         set(zrsh_srcdir "${cur_src}/${zrsh_srcdir}")
      endif()
   endif()
   if(NOT IS_DIRECTORY "${zrsh_srcdir}")
      message(FATAL_ERROR "The argument SRCDIR was invalid, "
              "current input was '${ZRSH_SRCDIR}'.")
   endif()

   if(NOT ZRSH_GENDIR)
      set(zrsh_gendir "${cur_bin}")
   else()
      set(zrsh_gendir "${ZRSH_GENDIR}")
      if(NOT IS_ABSOLUTE "${zrsh_gendir}")
         set(zrsh_gendir "${cur_bin}/${zrsh_gendir}")
      endif()
   endif()
   if(NOT IS_ABSOLUTE "${zrsh_gendir}")
      message(FATAL_ERROR "The argument GENDIR was invalid, "
              "current input was '${ZRSH_GENDIR}'.")
   endif()

   if(NOT ZRSH_INSDIR)
      set(zrsh_insdir "${cur_ins}")
   else()
      set(zrsh_insdir "${ZRSH_INSDIR}")
      if(NOT IS_ABSOLUTE "${zrsh_insdir}")
         set(ZRSH_INSDIR "${prj_ins}/${zrsh_insdir}")
      endif()
   endif()
   if(NOT IS_ABSOLUTE "${zrsh_insdir}")
      message(FATAL_ERROR "The argument INSDIR was invalid, "
              "current input was '${ZRSH_INSDIR}'.")
   endif()

   if(NOT ZRSH_GRPNOM)
      string(REGEX REPLACE "^.*/" "" zrsh_grpnom "${cur_src}")
   else()
      set(zrsh_grpnom ${ZRSH_GRPNOM})
   endif()
   if(NOT zrsh_grpnom MATCHES "^[ 0-9A-Za-z/_-]+$")
      message(FATAL_ERROR "The argument GRPNOM was invalid, "
              "current input was '${ZRSH_GRPNOM}'.")
   endif()

   unset(zrsh_srcext)
   list(APPEND zrsh_srcext ${ZRSH_SRCEXT})
   if(ZRSH_C)
      list(APPEND zrsh_srcext ".h")
      list(APPEND zrsh_srcext ".c")
   endif()
   if(ZRSH_CPP)
      list(APPEND zrsh_srcext ".hpp")
      list(APPEND zrsh_srcext ".inl")
      list(APPEND zrsh_srcext ".cpp")
   endif()
   foreach(ext ${zrsh_srcext})
      if(NOT ext MATCHES "^([.][0-9A-Za-z]+)+$")
         message(FATAL_ERROR "A argument in SRCEXT was invalid, "
                 "the argument was '${ext}' in '${ZRSH_SRCEXT}'.")
      endif()
   endforeach()

   unset(zrsh_genext)
   if(NOT ZRSH_GENEXT)
      list(APPEND zrsh_genext ".in")
   else()
      list(APPEND zrsh_genext ${ZRSH_GENEXT})
   endif()
   foreach(ext ${zrsh_genext})
      if(NOT ext MATCHES "^([.][0-9A-Za-z]+)+$")
         message(FATAL_ERROR "A argument in GENEXT was invalid, "
                 "the argument was '${ext}' in '${ZRSH_GENEXT}'.")
      endif()
   endforeach()

   unset(zrsh_insext)
   list(APPEND zrsh_insext ${ZRSH_INSEXT})
   if(ZRSH_C)
      list(APPEND zrsh_insext ".h")
   endif()
   if(ZRSH_CPP)
      list(APPEND zrsh_insext ".hpp")
      list(APPEND zrsh_insext ".inl")
   endif()
   foreach(ext ${zrsh_insext})
      if(NOT ext MATCHES "^([.][0-9A-Za-z]+)+$")
         message(FATAL_ERROR "A argument in INSEXT was invalid, "
                 "the argument was '${ext}' in '${ZRSH_INSEXT}'.")
      endif()
   endforeach()

   zr_get_src(${ZRSH_RECURSE}
              SRCVAR ${ZRSH_SRCVAR}
              SRCDIR ${zrsh_srcdir}
              GRPNOM ${zrsh_grpnom}
              SRCEXT ${zrsh_srcext})

   if(ZRSH_GENERATE)
      zr_gen_src(${ZRSH_RECURSE}
                 SRCVAR ${ZRSH_SRCVAR}
                 SRCDIR ${zrsh_srcdir}
                 GENDIR ${zrsh_gendir}
                 GRPNOM ${zrsh_grpnom}
                 GENEXT ${zrsh_genext})
   endif()

   if(ZRSH_INSTALL)
      zr_ins_src(${ZRSH_RECURSE}
                 SRCDIR ${zrsh_srcdir}
                 INSDIR ${zrsh_insdir}
                 INSEXT ${zrsh_insext})
   endif()

   if(ZRSH_GENERATE AND ZRSH_INSTALL)
      zr_ins_src(${ZRSH_RECURSE}
                 SRCDIR ${zrsh_gendir}
                 INSDIR ${zrsh_insdir}
                 INSEXT ${zrsh_insext})
   endif()
endmacro()
