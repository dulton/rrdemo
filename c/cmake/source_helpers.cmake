#-------------------------------------------------------------------------------
# SOURCE HELPERS
# 
# \sa [macro — CMake 3.6.1 Documentation](
#    http://cmake.org/cmake/help/v3.6/command/macro.html)
# \sa [function — CMake 3.6.1 Documentation](
#    http://cmake.org/cmake/help/v3.6/command/function.html)
#-------------------------------------------------------------------------------
# \author zhengrr
# \date 2016-8-11 ~ 17
# \copyright The MIT License
#-------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)
cmake_policy(SET CMP0057 NEW)  # CMake 3.3+

#-----------------------------------------------------------
# \brief Source Helper - Source
# \since 2016-8-15
#-----------------------------------------------------------
macro(srchlp_source)
   set(options "RECURSE")  # [in] Enable recurse.
   set(oneargs "SRCVAR"    # [out] Source variable, matchs regex.
               "SRCDIR"    # [in] Source directory, absolute path, need exist.
               "GRPNOM" )  # [in] Group name, matchs regex.
   set(mutargs "SRCEXT" )  # [in] Source extensions, matchs regex.
   cmake_parse_arguments("ARG" "${options}" "${oneargs}" "${mutargs}" ${ARGN})
   
   if(ARG_RECURSE)
      set(ARG_RECURSE "_RECURSE")
   else()
      set(ARG_RECURSE "")
   endif()
   
   if((NOT ARG_SRCVAR) OR
      (NOT ARG_SRCVAR MATCHES "^[0-9A-Za-z_-]+$"))
      message(FATAL_ERROR "The argument SRCVAR was null or invalid, "
                          "current input was '${ARG_SRCVAR}'.")
   endif()
   
   if((NOT ARG_SRCDIR) OR
      (NOT IS_DIRECTORY ${ARG_SRCDIR}))
      message(FATAL_ERROR "The argument SRCDIR was null or invalid, "
                          "current input was '${ARG_SRCDIR}'.")
   endif()
   
   if((NOT ARG_GRPNOM) OR
      (NOT ARG_GRPNOM MATCHES "^[ 0-9A-Za-z/_-]+$"))
      message(FATAL_ERROR "The argument GRPNOM was null or invalid, "
                          "current input was '${ARG_GRPNOM}'.")
   endif()
   
   if(NOT ARG_SRCEXT)
      message(FATAL_ERROR "The argument SRCEXT was null.")
   endif()
   foreach(ext ${ARG_SRCEXT})
      if(NOT ext MATCHES "^([.][0-9A-Za-z]+)+$")
         message(FATAL_ERROR "A argument in SRCEXT was invalid, "
                             "the argument was '${ext}' in '${ARG_SRCEXT}'.")
      endif()
   endforeach()
   
   unset(exts)
   foreach(ext ${ARG_SRCEXT})
   if(NOT ext IN_LIST exts)
   list(APPEND exts ${ext})
      file(GLOB${ARG_RECURSE} src "${ARG_SRCDIR}/*${ext}")
      foreach(file ${src})
         # common
         get_filename_component(dir ${file} DIRECTORY)               # dir
         string(REGEX REPLACE "^${ARG_SRCDIR}" "" reldir ${dir})     # reldir
         string(REPLACE "/" "\\\\" grpnom "${ARG_GRPNOM}${reldir}")  # grpnom
         # src list
         if(NOT file IN_LIST ${ARG_SRCVAR})
            list(APPEND ${ARG_SRCVAR} ${file})
         endif()
         # src group
         source_group(${grpnom} FILES ${file})
      endforeach()
   endif()
   endforeach()
endmacro()

#-----------------------------------------------------------
# \brief Source Helper - Generate
# \since 2016-8-15
#-----------------------------------------------------------
macro(srchlp_generate)
   set(options "RECURSE")  # [in] Enable recurse.
   set(oneargs "SRCVAR"    # [out] Source variable, matchs regex.
               "SRCDIR"    # [in] Source directory, absolute path, need exist.
               "GENDIR"    # [in] Generated directory, absolute path.
               "GRPNOM" )  # [in] Group name, matchs regex.
   set(mutargs "GENEXT" )  # [in] Generating source extensions, matchs regex.
   cmake_parse_arguments("ARG" "${options}" "${oneargs}" "${mutargs}" ${ARGN})
   
   if(ARG_RECURSE)
      set(ARG_RECURSE "_RECURSE")
   else()
      set(ARG_RECURSE "")
   endif()
   
   if((NOT ARG_SRCVAR) OR
      (NOT ARG_SRCVAR MATCHES "^[0-9A-Za-z_-]+$"))
      message(FATAL_ERROR "The argument SRCVAR was null or invalid, "
                          "current input was '${ARG_SRCVAR}'.")
   endif()
   
   if((NOT ARG_SRCDIR) OR
      (NOT IS_DIRECTORY ${ARG_SRCDIR}))
      message(FATAL_ERROR "The argument SRCDIR was null or invalid, "
                          "current input was '${ARG_SRCDIR}'.")
   endif()
   
   if((NOT ARG_GENDIR) OR
      (NOT IS_ABSOLUTE ${ARG_GENDIR}))
      message(FATAL_ERROR "The argument GENDIR was null or invalid, "
                          "current input was '${ARG_GENDIR}'.")
   endif()
   
   if((NOT ARG_GRPNOM) OR
      (NOT ARG_GRPNOM MATCHES "^[ 0-9A-Za-z/_-]+$"))
      message(FATAL_ERROR "The argument GRPNOM was null or invalid, "
                          "current input was '${ARG_GRPNOM}'.")
   endif()
   
   if(NOT ARG_GENEXT)
      message(FATAL_ERROR "The argument GENEXT was null.")
   endif()
   foreach(ext ${ARG_GENEXT})
      if(NOT ext MATCHES "^([.][0-9A-Za-z]+)+$")
         message(FATAL_ERROR "A argument in GENEXT was invalid, "
                             "the argument was '${ext}' in '${ARG_GENEXT}'.")
      endif()
   endforeach()
   
   unset(exts)
   foreach(ext ${ARG_GENEXT})
   if(NOT ext IN_LIST exts)
   list(APPEND exts ${ext})
      file(GLOB${ARG_RECURSE} src "${ARG_SRCDIR}/*${ext}")
      foreach(file ${src})
         # common
         get_filename_component(dir ${file} DIRECTORY)               # dir
         get_filename_component(nom ${file} NAME)                    # nom
         string(REPLACE "." "\\." extrgx "${ext}")                   # extrgx
         string(REGEX REPLACE "^${ARG_SRCDIR}" "" reldir ${dir})     # reldir
         string(REPLACE "/" "\\\\" grpnom "${ARG_GRPNOM}${reldir}")  # grpnom
         string(REGEX REPLACE "${extrgx}$" "" gennom ${nom})         # gennom
         set(genfile "${ARG_GENDIR}${reldir}/${gennom}")             # genfile
         # src list
         if(NOT file IN_LIST ${ARG_SRCVAR})
            list(APPEND ${ARG_SRCVAR} ${file})
         endif()
         # src group
         source_group(${grpnom} FILES ${file})
         # gen & gen list
         if(NOT genfile IN_LIST ${ARG_SRCVAR})
            configure_file(${file} ${genfile} @ONLY)
            list(APPEND ${ARG_SRCVAR} ${genfile})
         endif()
         # gen group
         source_group(${grpnom} FILES ${genfile})
      endforeach()
   endif()
   endforeach()
endmacro()

#-----------------------------------------------------------
# \brief Source Helper - Install
# \since 2016-8-15
#-----------------------------------------------------------
function(srchlp_install)
   set(options "RECURSE")  # [in] Enable recurse.
   set(oneargs "SRCDIR"    # [in] Source directory, absolute path, need exist.
               "INSDIR" )  # [in] Install directory, absolute path.
   set(mutargs "INSEXT" )  # [in] Installing source extensions, matchs regex.
   cmake_parse_arguments("ARG" "${options}" "${oneargs}" "${mutargs}" ${ARGN})
   
   if(ARG_RECURSE)
      set(ARG_RECURSE "_RECURSE")
   else()
      set(ARG_RECURSE "")
   endif()
   
   if((NOT ARG_SRCDIR) OR
      (NOT IS_DIRECTORY ${ARG_SRCDIR}))
      message(FATAL_ERROR "The argument SRCDIR was null or invalid, "
                          "current input was '${ARG_SRCDIR}'.")
   endif()
   
   if((NOT ARG_INSDIR) OR
      (NOT IS_ABSOLUTE ${ARG_INSDIR}))
      message(FATAL_ERROR "The argument INSDIR was null or invalid, "
                          "current input was '${ARG_INSDIR}'.")
   endif()
   
   if(NOT ARG_INSEXT)
      message(FATAL_ERROR "The argument INSEXT was null.")
   endif()
   foreach(ext ${ARG_INSEXT})
      if(NOT ext MATCHES "^([.][0-9A-Za-z]+)+$")
         message(FATAL_ERROR "A argument in INSEXT was invalid, "
                             "the argument was '${ext}' in '${ARG_INSEXT}'.")
      endif()
   endforeach()
   
   unset(exts)
   foreach(ext ${ARG_INSEXT})
   if(NOT ext IN_LIST exts)
   list(APPEND exts ${ext})
      file(GLOB${ARG_RECURSE} src "${ARG_SRCDIR}/*${ext}")
      foreach(file ${src})
         # common
         get_filename_component(dir ${file} DIRECTORY)            # dir
         string(REGEX REPLACE "^${ARG_SRCDIR}" "" reldir ${dir})  # reldir
         # install
         install(FILES ${file}  DESTINATION "${ARG_INSDIR}${reldir}")
      endforeach()
   endif()
   endforeach()
endfunction()

#-----------------------------------------------------------
# \brief Source Helper
# \since 2016-8-11
#-----------------------------------------------------------
macro(source_helper)
   set(options "GENERATE"  # [in] Enable source generating.
               "INSTALL"   # [in] Enable source install.
               "RECURSE"   # [in] Enable recurse.
               "C"         # [in] Some extensions for C.
               "CPP"    )  # [in] Some extensions for CPP.
   set(oneargs "SRCVAR"    # [out] Source variable, matchs regex
               "SRCDIR"    # [in] Source directory,
                           #         default current source directory.
               "GENDIR"    # [in] Generated directory,
                           #         default current build directory.
               "INSDIR"    # [in] Install directory,
                           #         default current install directory.
               "GRPNOM" )  # [in] Group name,
                           #         default current parent directory.
   set(mutargs "SRCEXT"    # [in] Source extensions, matchs regex
               "GENEXT"    # [in] Generating source extensions, matchs regex
               "INSEXT" )  # [in] Installing source extensions, matchs regex
   cmake_parse_arguments("SRCHLP" "${options}" "${oneargs}" "${mutargs}" ${ARGN})

   string(TOLOWER "${PROJECT_NAME}" DEF_PRJNOMLWR)
   set(DEF_PRJSRCDIR "${PROJECT_SOURCE_DIR}")
   set(DEF_CURSRCDIR "${CMAKE_CURRENT_LIST_DIR}")
   string(REGEX REPLACE "^${DEF_PRJSRCDIR}" "" DEF_RELDIR "${DEF_CURSRCDIR}")
   set(DEF_PRJBINDIR "${PROJECT_BINARY_DIR}")
   set(DEF_CURBINDIR "${DEF_PRJBINDIR}${DEF_RELDIR}")
   set(DEF_PRJINSDIR "${CMAKE_INSTALL_PREFIX}")
   set(DEF_CURINSDIR "${DEF_PRJINSDIR}/include/${DEF_PRJNOMLWR}")

   if(SRCHLP_RECURSE)
      set(SRCHLP_RECURSE "RECURSE")
   else()
      set(SRCHLP_RECURSE "")
   endif()

   if((NOT SRCHLP_SRCVAR) OR
      (NOT SRCHLP_SRCVAR MATCHES "^[0-9A-Za-z_-]+$"))
      message(FATAL_ERROR "The argument SRCVAR was null or invalid, "
                          "current input was '${SRCHLP_SRCVAR}'.")
   endif()

   if(NOT SRCHLP_SRCDIR)
      set(SRCHLP_SRCDIR "${DEF_CURSRCDIR}")
   endif()
   if(NOT IS_DIRECTORY "${SRCHLP_SRCDIR}")
      set(SRCHLP_SRCDIR "${DEF_CURSRCDIR}/${SRCHLP_SRCDIR}")
   endif()
   if(NOT IS_DIRECTORY "${SRCHLP_SRCDIR}")
      message(FATAL_ERROR "The argument SRCDIR was invalid, "
                          "current input was '${SRCHLP_SRCDIR}'.")
   endif()

   if(NOT SRCHLP_GENDIR)
      set(SRCHLP_GENDIR "${DEF_CURBINDIR}")
   endif()
   if(NOT IS_ABSOLUTE "${SRCHLP_GENDIR}")
      set(SRCHLP_GENDIR "${DEF_CURBINDIR}/${SRCHLP_GENDIR}")
   endif()
   if(NOT IS_ABSOLUTE "${SRCHLP_SRCDIR}")
      message(FATAL_ERROR "The argument GENDIR was invalid, "
                          "current input was '${SRCHLP_GENDIR}'.")
   endif()

   if(NOT SRCHLP_INSDIR)
      set(SRCHLP_INSDIR "${DEF_CURINSDIR}")
   endif()
   if(NOT IS_ABSOLUTE "${SRCHLP_INSDIR}")
      set(SRCHLP_INSDIR "${DEF_PRJINSDIR}/${SRCHLP_INSDIR}")
   endif()
   if(NOT IS_ABSOLUTE "${SRCHLP_INSDIR}")
      message(FATAL_ERROR "The argument INSDIR was invalid, "
                          "current input was '${SRCHLP_INSDIR}'.")
   endif()

   if(NOT SRCHLP_GRPNOM)
      string(REGEX REPLACE "^.*/" "" SRCHLP_GRPNOM "${DEF_CURSRCDIR}")
   endif()
   if(NOT SRCHLP_GRPNOM MATCHES "^[ 0-9A-Za-z/_-]+$")
      message(FATAL_ERROR "The argument GRPNOM was invalid, "
                          "current input was '${SRCHLP_GRPNOM}'.")
   endif()

   if(SRCHLP_C)
      list(APPEND SRCHLP_SRCEXT ".h")
      list(APPEND SRCHLP_SRCEXT ".inth")
      list(APPEND SRCHLP_SRCEXT ".c")
   endif()
   if(SRCHLP_CPP)
      list(APPEND SRCHLP_SRCEXT ".hpp")
      list(APPEND SRCHLP_SRCEXT ".inl")
      list(APPEND SRCHLP_SRCEXT ".inthpp")
      list(APPEND SRCHLP_SRCEXT ".cpp")
   endif()
   foreach(ext ${SRCHLP_SRCEXT})
      if(NOT ext MATCHES "^([.][0-9A-Za-z]+)+$")
         message(FATAL_ERROR "A argument in SRCEXT was invalid, "
                             "the argument was '${ext}' in '${SRCHLP_SRCEXT}'.")
      endif()
   endforeach()

   if(NOT SRCHLP_GENEXT)
      list(APPEND SRCHLP_GENEXT ".in")
   endif()
   foreach(ext ${SRCHLP_GENEXT})
      if(NOT ext MATCHES "^([.][0-9A-Za-z]+)+$")
         message(FATAL_ERROR "A argument in GENEXT was invalid, "
                             "the argument was '${ext}' in '${SRCHLP_GENEXT}'.")
      endif()
   endforeach()

   if(SRCHLP_C)
      list(APPEND SRCHLP_INSEXT ".h")
   endif()
   if(SRCHLP_CPP)
      list(APPEND SRCHLP_INSEXT ".hpp")
      list(APPEND SRCHLP_INSEXT ".inl")
   endif()
   foreach(ext ${SRCHLP_INSEXT})
      if(NOT ext MATCHES "^([.][0-9A-Za-z]+)+$")
         message(FATAL_ERROR "A argument in INSEXT was invalid, "
                             "the argument was '${ext}' in '${SRCHLP_INSEXT}'.")
      endif()
   endforeach()

   srchlp_source(${SRCHLP_RECURSE}
                 SRCVAR ${SRCHLP_SRCVAR}
                 SRCDIR ${SRCHLP_SRCDIR}
                 GRPNOM ${SRCHLP_GRPNOM}
                 SRCEXT ${SRCHLP_SRCEXT})

   if(SRCHLP_GENERATE)
      srchlp_generate(${SRCHLP_RECURSE}
                      SRCVAR ${SRCHLP_SRCVAR}
                      SRCDIR ${SRCHLP_SRCDIR}
                      GENDIR ${SRCHLP_GENDIR}
                      GRPNOM ${SRCHLP_GRPNOM}
                      GENEXT ${SRCHLP_GENEXT})
   endif()

   if(SRCHLP_INSTALL)
      srchlp_install(${SRCHLP_RECURSE}
                     SRCDIR ${SRCHLP_SRCDIR}
                     INSDIR ${SRCHLP_INSDIR}
                     INSEXT ${SRCHLP_INSEXT})
   endif()

   if(SRCHLP_GENERATE AND SRCHLP_INSTALL)
      srchlp_install(${SRCHLP_RECURSE}
                     SRCDIR ${SRCHLP_GENDIR}
                     INSDIR ${SRCHLP_INSDIR}
                     INSEXT ${SRCHLP_INSEXT})
   endif()
endmacro()
