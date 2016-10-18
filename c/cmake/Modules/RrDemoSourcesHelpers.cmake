#==============================================================================#
# \file
# \brief RrDemo Sources Helpers
# \author zhengrr
# \date 2016-10-8 – 10-9
# \copyright The MIT License
#==============================================================================#
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)
cmake_policy(SET CMP0057 NEW)  # CMake 3.3+

#------------------------------------------------------------------------------#
# \brief Find Sources
# \since 2016-9-30 – 10-9
#------------------------------------------------------------------------------#
function(rrdemo_find_sources)
   set(opts
       "RECURSE")  # [in] Enable recurse.
   set(ones
       "SRCVAR"    # [out] Sources variable, matchs regex.
       "SRCDIR"    # [in] Sources directory, absolute path, need exist.
       "GRPDIR")   # [in] Group directory, matchs regex.
   set(muts
       "SRCEXTS")  # [in] Source extensions, matchs regex.
   cmake_parse_arguments("ARG" "${opts}" "${ones}" "${muts}" ${ARGN})

   if(ARG_RECURSE)
      set(ARG_RECURSE "_RECURSE")
   else()
      set(ARG_RECURSE "")
   endif()

   if((NOT ARG_SRCVAR) OR (NOT ARG_SRCVAR MATCHES "^[0-9A-Za-z_-]+$"))
      message(FATAL_ERROR "The argument SRCVAR was null or invalid, "
              "current input was '${ARG_SRCVAR}'.")
   endif()

   if((NOT ARG_SRCDIR) OR (NOT IS_DIRECTORY "${ARG_SRCDIR}"))
      message(FATAL_ERROR "The argument SRCDIR was null or invalid, "
              "current input was '${ARG_SRCDIR}'.")
   endif()

   if((NOT ARG_GRPDIR) OR (NOT ARG_GRPDIR MATCHES "^[ 0-9A-Za-z/_-]+$"))
      message(FATAL_ERROR "The argument GRPDIR was null or invalid, "
              "current input was '${ARG_GRPDIR}'.")
   endif()

   if(NOT ARG_SRCEXTS)
      message(FATAL_ERROR "The argument SRCEXTS was null.")
   endif()
   foreach(ext ${ARG_SRCEXTS})
      if(NOT ext MATCHES "^([.][0-9A-Za-z]+)+$")
         message(FATAL_ERROR "A argument in SRCEXTS was invalid, "
                 "the argument was '${ext}' in '${ARG_SRCEXTS}'.")
      endif()
   endforeach()

   unset(exts)
   foreach(ext ${ARG_SRCEXTS})
      if(NOT ext IN_LIST exts)
         list(APPEND exts "${ext}")
         file(GLOB${ARG_RECURSE} src "${ARG_SRCDIR}/*${ext}")
         foreach(file ${src})
            # append file
            if(NOT ${file} IN_LIST ${ARG_SRCVAR})
               list(APPEND ${ARG_SRCVAR} "${file}")
               set(${ARG_SRCVAR} ${${ARG_SRCVAR}} "${file}")
            endif()
            # group file
            get_filename_component(fdir "${file}" DIRECTORY)
            string(REGEX REPLACE "^${ARG_SRCDIR}" "" freldir "${fdir}")
            string(REPLACE "/" "\\\\" fgrpdir "${ARG_GRPDIR}${freldir}")
            source_group("${fgrpdir}" FILES "${file}")
         endforeach()
      endif()
   endforeach()

   set(${ARG_SRCVAR} ${${ARG_SRCVAR}} PARENT_SCOPE)
endfunction()

#------------------------------------------------------------------------------#
# \brief Generate Sources
# \since 2016-9-30 – 10-9
#------------------------------------------------------------------------------#
function(rrdemo_generate_sources)
   set(opts
       "RECURSE")  # [in] Enable recurse.
   set(ones
       "SRCVAR"    # [out] Sources variable, matchs regex.
       "SRCDIR"    # [in] Sources directory, absolute path, need exist.
       "GENDIR"    # [in] Generated directory, absolute path.
       "GRPDIR")   # [in] Group directory, matchs regex.
   set(muts
       "GENEXTS")  # [in] Generating source extensions, matchs regex.
   cmake_parse_arguments("ARG" "${opts}" "${ones}" "${muts}" ${ARGN})

   if(ARG_RECURSE)
      set(ARG_RECURSE "_RECURSE")
   else()
      set(ARG_RECURSE "")
   endif()

   if((NOT ARG_SRCVAR) OR (NOT ARG_SRCVAR MATCHES "^[0-9A-Za-z_-]+$"))
      message(FATAL_ERROR "The argument SRCVAR was null or invalid, "
              "current input was '${ARG_SRCVAR}'.")
   endif()

   if((NOT ARG_SRCDIR) OR (NOT IS_DIRECTORY "${ARG_SRCDIR}"))
      message(FATAL_ERROR "The argument SRCDIR was null or invalid, "
              "current input was '${ARG_SRCDIR}'.")
   endif()

   if((NOT ARG_GENDIR) OR (NOT IS_ABSOLUTE "${ARG_GENDIR}"))
      message(FATAL_ERROR "The argument GENDIR was null or invalid, "
              "current input was '${ARG_GENDIR}'.")
   endif()

   if((NOT ARG_GRPDIR) OR (NOT ARG_GRPDIR MATCHES "^[ 0-9A-Za-z/_-]+$"))
      message(FATAL_ERROR "The argument GRPDIR was null or invalid, "
              "current input was '${ARG_GRPDIR}'.")
   endif()

   if(NOT ARG_GENEXTS)
      message(FATAL_ERROR "The argument GENEXTS was null.")
   endif()
   foreach(ext ${ARG_GENEXTS})
      if(NOT ext MATCHES "^([.][0-9A-Za-z]+)+$")
         message(FATAL_ERROR "A argument in GENEXTS was invalid, "
                 "the argument was '${ext}' in '${ARG_GENEXTS}'.")
      endif()
   endforeach()

   unset(exts)
   foreach(ext ${ARG_GENEXTS})
      if(NOT ext IN_LIST exts)
         list(APPEND exts "${ext}")
         file(GLOB${ARG_RECURSE} src "${ARG_SRCDIR}/*${ext}")
         foreach(file ${src})
            # append file
            if(NOT file IN_LIST ${ARG_SRCVAR})
               list(APPEND ${ARG_SRCVAR} "${file}")
            endif()
            # group file
            get_filename_component(fdir "${file}" DIRECTORY)
            string(REGEX REPLACE "^${ARG_SRCDIR}" "" freldir "${fdir}")
            string(REPLACE "/" "\\\\" fgrpdir "${ARG_GRPDIR}${freldir}")
            source_group("${fgrpdir}" FILES "${file}")
            # generate, append & group (generated) file
            get_filename_component(fname "${file}" NAME)
            string(REPLACE "." "\\." extrgx "${ext}")
            string(REGEX REPLACE "${extrgx}$" "" gname "${fname}")
            set(gfile "${ARG_GENDIR}${freldir}/${gname}")
            if(NOT gfile IN_LIST ${ARG_SRCVAR})
               configure_file("${file}" "${gfile}" @ONLY)
               list(APPEND ${ARG_SRCVAR} "${gfile}")
               source_group("${fgrpdir}" FILES "${gfile}")
            endif()
         endforeach()
      endif()
   endforeach()

   set(${ARG_SRCVAR} ${${ARG_SRCVAR}} PARENT_SCOPE)
endfunction()

#------------------------------------------------------------------------------#
# \brief Install Source
# \since 2016-9-30 – 10-9
#------------------------------------------------------------------------------#
function(rrdemo_install_sources)
   set(opts
       "RECURSE")  # [in] Enable recurse.
   set(ones
       "SRCDIR"    # [in] Source directory, absolute path, need exist.
       "INSDIR")   # [in] Install directory, absolute path.
   set(muts
       "INSEXTS")  # [in] Installing source extensions, matchs regex.
   cmake_parse_arguments("ARG" "${opts}" "${ones}" "${muts}" ${ARGN})

   if(ARG_RECURSE)
      set(ARG_RECURSE "_RECURSE")
   else()
      set(ARG_RECURSE "")
   endif()

   if((NOT ARG_SRCDIR) OR (NOT IS_DIRECTORY "${ARG_SRCDIR}"))
      message(FATAL_ERROR "The argument SRCDIR was null or invalid, "
              "current input was '${ARG_SRCDIR}'.")
   endif()

   if((NOT ARG_INSDIR) OR (NOT IS_ABSOLUTE "${ARG_INSDIR}"))
      message(FATAL_ERROR "The argument INSDIR was null or invalid, "
              "current input was '${ARG_INSDIR}'.")
   endif()

   if(NOT ARG_INSEXTS)
      message(FATAL_ERROR "The argument INSEXTS was null.")
   endif()
   foreach(ext ${ARG_INSEXTS})
      if(NOT ext MATCHES "^([.][0-9A-Za-z]+)+$")
         message(FATAL_ERROR "A argument in INSEXTS was invalid, "
                 "the argument was '${ext}' in '${ARG_INSEXTS}'.")
      endif()
   endforeach()

   unset(exts)
   foreach(ext ${ARG_INSEXTS})
      if(NOT ext IN_LIST exts)
         list(APPEND exts ${ext})
         file(GLOB${ARG_RECURSE} src "${ARG_SRCDIR}/*${ext}")
         foreach(file ${src})
            # install file
            get_filename_component(fdir "${file}" DIRECTORY)
            string(REGEX REPLACE "^${ARG_SRCDIR}" "" freldir "${fdir}")
            install(FILES "${file}" DESTINATION "${ARG_INSDIR}${freldir}")
         endforeach()
      endif()
   endforeach()
endfunction()

#------------------------------------------------------------------------------#
# \brief Sources
# \since 2016-9-30 – 10-9
#------------------------------------------------------------------------------#
function(rrdemo_sources)
   set(opts
       "GENERATE"  # [in] Enable source generating.
       "INSTALL"   # [in] Enable source installing.
       "RECURSE"   # [in] Enable recurse.
       "C"         # [in] Some extensions for C.
       "CPP"       # [in] Some extensions for C++.
       "QT")       # [in] Some extensions for Qt.
   set(ones
       "SRCVAR"    # [out] Source variable, matchs regex
       "SRCDIR"    # [in] Source directory, default current source directory.
       "GENDIR"    # [in] Generated directory, default current build directory.
       "INSDIR"    # [in] Install directory, default current install directory.
       "GRPDIR")   # [in] Group directory, default current parent directory.
   set(muts
       "SRCEXTS"   # [in] Source extensions, matchs regex.
       "GENEXTS"   # [in] Generating source extensions, matchs regex.
       "INSEXTS")  # [in] Installing source extensions, matchs regex.
   cmake_parse_arguments("ARG" "${opts}" "${ones}" "${muts}" ${ARGN})

   set(prjsrc "${PROJECT_SOURCE_DIR}")
   set(cursrc "${CMAKE_CURRENT_LIST_DIR}")
   string(REGEX REPLACE "^${prjsrc}" "" reldir "${cursrc}")
   set(prjbin "${PROJECT_BINARY_DIR}")
   set(curbin "${prjbin}${reldir}")
   string(TOLOWER "${PROJECT_NAME}" prjlow)
   set(prjins "${CMAKE_INSTALL_PREFIX}")
   set(curins "${prjins}/include/${prjlow}")

   if(ARG_RECURSE)
      set(ARG_RECURSE "RECURSE")
   else()
      set(ARG_RECURSE "")
   endif()

   if((NOT ARG_SRCVAR) OR (NOT ARG_SRCVAR MATCHES "^[0-9A-Za-z_-]+$"))
      message(FATAL_ERROR "The argument SRCVAR was null or invalid, "
              "current input was '${ARG_SRCVAR}'.")
   endif()

   if(NOT ARG_SRCDIR)
      set(ARG_SRCDIR "${cursrc}")
   else()
      if(NOT IS_DIRECTORY "${ARG_SRCDIR}")
         set(ARG_SRCDIR "${cursrc}/${ARG_SRCDIR}")
      endif()
   endif()
   if(NOT IS_DIRECTORY "${ARG_SRCDIR}")
      message(FATAL_ERROR "The argument SRCDIR was invalid, "
              "current value was '${ARG_SRCDIR}'.")
   endif()

   if(NOT ARG_GENDIR)
      set(ARG_GENDIR "${curbin}")
   else()
      if(NOT IS_ABSOLUTE "${ARG_GENDIR}")
         set(ARG_GENDIR "${curbin}/${ARG_GENDIR}")
      endif()
   endif()
   if(NOT IS_ABSOLUTE "${ARG_GENDIR}")
      message(FATAL_ERROR "The argument GENDIR was invalid, "
              "current value was '${ARG_GENDIR}'.")
   endif()

   if(NOT ARG_INSDIR)
      set(ARG_INSDIR "${curins}")
   else()
      if(NOT IS_ABSOLUTE "${ARG_INSDIR}")
         set(ARG_INSDIR "${curins}/${ARG_INSDIR}")
      endif()
   endif()
   if(NOT IS_ABSOLUTE "${ARG_INSDIR}")
      message(FATAL_ERROR "The argument INSDIR was invalid, "
              "current value was '${ARG_INSDIR}'.")
   endif()

   if(NOT ARG_GRPDIR)
      string(REGEX REPLACE "^.*/" "" ARG_GRPDIR "${cursrc}")
   endif()
   if(NOT ARG_GRPDIR MATCHES "^[ 0-9A-Za-z/_-]+$")
      message(FATAL_ERROR "The argument GRPDIR was invalid, "
              "current input was '${ARG_GRPDIR}'.")
   endif()

   if(ARG_C)
      list(APPEND ARG_SRCEXTS ".h")
      list(APPEND ARG_SRCEXTS ".c")
   endif()
   if(ARG_CPP)
      list(APPEND ARG_SRCEXTS ".hpp")
      list(APPEND ARG_SRCEXTS ".inl")
      list(APPEND ARG_SRCEXTS ".cpp")
   endif()
   if(ARG_QT)
      list(APPEND ARG_SRCEXTS ".ui")
      list(APPEND ARG_SRCEXTS ".qrc")
   endif()
   foreach(ext ${ARG_SRCEXTS})
      if(NOT ext MATCHES "^([.][0-9A-Za-z]+)+$")
         message(FATAL_ERROR "A argument in SRCEXTS was invalid, "
                 "the argument was '${ext}' in '${ARG_SRCEXTS}'.")
      endif()
   endforeach()

   if(NOT ARG_GENEXTS)
      list(APPEND ARG_GENEXTS ".in")
   endif()
   foreach(ext ${ARG_GENEXTS})
      if(NOT ext MATCHES "^([.][0-9A-Za-z]+)+$")
         message(FATAL_ERROR "A argument in GENEXTS was invalid, "
                 "the argument was '${ext}' in '${ARG_GENEXTS}'.")
      endif()
   endforeach()

   if(ARG_C)
      list(APPEND ARG_INSEXTS ".h")
   endif()
   if(ARG_CPP)
      list(APPEND ARG_INSEXTS ".hpp")
      list(APPEND ARG_INSEXTS ".inl")
   endif()
   foreach(ext ${ARG_INSEXTS})
      if(NOT ext MATCHES "^([.][0-9A-Za-z]+)+$")
         message(FATAL_ERROR "A argument in INSEXTS was invalid, "
                 "the argument was '${ext}' in '${ARG_INSEXTS}'.")
      endif()
   endforeach()

   rrdemo_find_sources(${ARG_RECURSE}
                       SRCVAR ${ARG_SRCVAR}
                       SRCDIR ${ARG_SRCDIR}
                       GRPDIR ${ARG_GRPDIR}
                       SRCEXTS ${ARG_SRCEXTS})

   if(ARG_GENERATE)
      rrdemo_generate_sources(${ARG_RECURSE}
                              SRCVAR ${ARG_SRCVAR}
                              SRCDIR ${ARG_SRCDIR}
                              GENDIR ${ARG_GENDIR}
                              GRPDIR ${ARG_GRPDIR}
                              GENEXTS ${ARG_GENEXTS})
   endif()

   if(ARG_INSTALL)
      rrdemo_install_sources(${ARG_RECURSE}
                             SRCDIR ${ARG_SRCDIR}
                             INSDIR ${ARG_INSDIR}
                             INSEXTS ${ARG_INSEXTS})
   endif()

   if(ARG_GENERATE AND ARG_INSTALL)
      rrdemo_install_sources(${ARG_RECURSE}
                             SRCDIR ${ARG_GENDIR}
                             INSDIR ${ARG_INSDIR}
                             INSEXTS ${ARG_INSEXTS})
   endif()

   set(${ARG_SRCVAR} ${${ARG_SRCVAR}} PARENT_SCOPE)
endfunction()
