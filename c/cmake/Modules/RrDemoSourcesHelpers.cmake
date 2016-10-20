# zhengrr
# 2016-10-8 – 20
# The MIT License

#[======================================================================[.rst:
RrDemo Sources Helpers
----------------------

Find, group, generate & install sources by directory, for RrDemo.

CMake 3.3+ required.

Module Function/Macros
^^^^^^^^^^^^^^^^^^^^^^
#]======================================================================]
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)
cmake_policy(SET CMP0057 NEW)  # CMake 3.3+

#[==================================================[.rst:
.. command:: rrdemo_find_sources

  ::

    rrdemo_find_sources(
      [RECURSE]
      SRCVAR <src-var>
      SRCDIR <src-dir>
      GRPDIR <grp-dir>
      SRCEXTS <src-ext>...
      )

  This function accepts the following named parameters:

  ``RECURSE``
    enable recurse
  ``SRCVAR <src-var>``
    sources variable, matchs regex ``^[0-9A-Za-z_-]+$``
  ``SRCDIR <src-dir>``
    sources directory, absolute path, must exist
  ``GRPDIR <grp-dir>``
    group directory, matchs regex ``^[ 0-9A-Z\\a-z/_-]+$``
  ``SRCEXTS <src-ext>...``
    source extensions, matchs regex ``^([.][^ \"%*./:<>?\\|]+)+$``
#]==================================================]
function(rrdemo_find_sources)
  set(opts "RECURSE")
  set(ones "SRCVAR" "SRCDIR" "GRPDIR")
  set(muts "SRCEXTS")
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

  if((NOT ARG_GRPDIR) OR (NOT ARG_GRPDIR MATCHES "^[ 0-9A-Z\\a-z/_-]+$"))
    message(FATAL_ERROR "The argument GRPDIR was null or invalid, "
      "current input was '${ARG_GRPDIR}'.")
  endif()

  if(NOT ARG_SRCEXTS)
    message(FATAL_ERROR "The argument SRCEXTS was null.")
  endif()
  foreach(ext ${ARG_SRCEXTS})
    if(NOT ext MATCHES "^([.][^ \"%*./:<>?\\|]+)+$")
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

#[==================================================[.rst:
.. command:: rrdemo_generate_sources

  ::

    rrdemo_generate_sources(
      [RECURSE]
      SRCVAR <src-var>
      SRCDIR <src-dir>
      GENDIR <gen-dir>
      GRPDIR <grp-dir>
      GENEXTS <gen-ext>...
      )

  This function accepts the following named parameters:

  ``RECURSE``
    enable recurse
  ``SRCVAR <src-var>``
    sources variable, matchs regex ``^[0-9A-Za-z_-]+$``
  ``SRCDIR <src-dir>``
    sources directory, absolute path, must exist
  ``GENDIR <gen-dir>``
    generated directory, absolute path
  ``GRPDIR <grp-dir>``
    group directory, matchs regex ``^[ 0-9A-Z\\a-z/_-]+$``
  ``GENEXTS <gen-ext>...``
    generating source extensions, matchs regex ``^([.][^ \"%*./:<>?\\|]+)+$``
#]==================================================]
function(rrdemo_generate_sources)
  set(opts "RECURSE")
  set(ones "SRCVAR" "SRCDIR" "GENDIR" "GRPDIR")
  set(muts "GENEXTS")
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

  if((NOT ARG_GRPDIR) OR (NOT ARG_GRPDIR MATCHES "^[ 0-9A-Z\\a-z/_-]+$"))
    message(FATAL_ERROR "The argument GRPDIR was null or invalid, "
      "current input was '${ARG_GRPDIR}'.")
  endif()

  if(NOT ARG_GENEXTS)
    message(FATAL_ERROR "The argument GENEXTS was null.")
  endif()
  foreach(ext ${ARG_GENEXTS})
    if(NOT ext MATCHES "^([.][^ \"%*./:<>?\\|]+)+$")
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

#[==================================================[.rst:
.. command:: rrdemo_install_sources

  ::

    rrdemo_install_sources(
      [RECURSE]
      SRCDIR <src-dir>
      INSDIR <ins-dir>
      INSEXTS <ins-ext>...
      )

  This function accepts the following named parameters:

  ``RECURSE``
    enable recurse
  ``SRCDIR <src-dir>``
    sources directory, absolute path, must exist
  ``INSDIR <ins-dir>``
    install directory, absolute path
  ``INSEXTS <ins-ext>...``
    installing source extensions, matchs regex ``^([.][^ \"%*./:<>?\\|]+)+$``
#]==================================================]
function(rrdemo_install_sources)
  set(opts "RECURSE")
  set(ones "SRCDIR" "INSDIR")
  set(muts "INSEXTS")
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
    if(NOT ext MATCHES "^([.][^ \"%*./:<>?\\|]+)+$")
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

#[==================================================[.rst:
.. command:: rrdemo_sources

  ::

    rrdemo_sources(
      [GENERATE] [INSTALL] [RECURSE] [C] [CPP] [QT]
      SRCVAR <src-var>
      [SRCDIR <src-dir>] [GENDIR <gen-dir>] [INSDIR <ins-dir>]
      [GRPDIR <grp-dir>]
      [SRCEXTS <src-ext>...] [GENEXTS <gen-ext>...] [INSEXTS <ins-ext>...]
    )

  This function accepts the following named parameters:

  ``GENERATE``
    enable source generating
  ``INSTALL``
    enable source installing
  ``RECURSE``
    enable recurse
  ``C``
    append some extensions for C
  ``CPP``
    append some extensions for C++
  ``QT``
    append some extensions for Qt
  ``SRCVAR <src-var>``
    sources variable, matchs regex ``^[0-9A-Za-z_-]+$``
  ``SRCDIR <src-dir>``
    sources directory, absolute path, must exist
    default current source directory
  ``GENDIR <gen-dir>``
    generated directory, absolute path
    default current build directory
  ``INSDIR <ins-dir>``
    install directory, absolute path
    default current install directory
  ``GRPDIR <grp-dir>``
    group directory, matchs regex ``^[ 0-9A-Z\\a-z/_-]+$``
    default current parent directory
  ``SRCEXTS <src-ext>...``
    source extensions, matchs regex ``^([.][^ \"%*./:<>?\\|]+)+$``
    if not enable preset, this is required
  ``GENEXTS <gen-ext>...``
    generating source extensions, matchs regex ``^([.][^ \"%*./:<>?\\|]+)+$``
    default ```.in```
  ``INSEXTS <ins-ext>...``
    installing source extensions, matchs regex ``^([.][^ \"%*./:<>?\\|]+)+$``
    if not enable preset, this is required
#]==================================================]
function(rrdemo_sources)
  set(opts "GENERATE" "INSTALL" "RECURSE" "C" "CPP" "QT")
  set(ones "SRCVAR" "SRCDIR" "GENDIR" "INSDIR" "GRPDIR")
  set(muts "SRCEXTS" "GENEXTS" "INSEXTS")
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
  if(NOT ARG_GRPDIR MATCHES "^[ 0-9A-Z\\a-z/_-]+$")
    message(FATAL_ERROR "The argument GRPDIR was invalid, "
      "current input was '${ARG_GRPDIR}'.")
  endif()

  if(ARG_C)
    list(APPEND ARG_SRCEXTS ".h" ".c")
  endif()
  if(ARG_CPP)
    list(APPEND ARG_SRCEXTS ".H" ".h++" ".hh" ".hpp" ".hxx" ".inl" ".C" ".c++" ".cc" ".cpp" ".cxx")
  endif()
  if(ARG_QT)
    list(APPEND ARG_SRCEXTS ".ui" ".qrc")
  endif()
  foreach(ext ${ARG_SRCEXTS})
    if(NOT ext MATCHES "^([.][^ \"%*./:<>?\\|]+)+$")
      message(FATAL_ERROR "A argument in SRCEXTS was invalid, "
        "the argument was '${ext}' in '${ARG_SRCEXTS}'.")
    endif()
  endforeach()

  if(NOT ARG_GENEXTS)
    list(APPEND ARG_GENEXTS ".in")
  endif()
  foreach(ext ${ARG_GENEXTS})
    if(NOT ext MATCHES "^([.][^ \"%*./:<>?\\|]+)+$")
      message(FATAL_ERROR "A argument in GENEXTS was invalid, "
        "the argument was '${ext}' in '${ARG_GENEXTS}'.")
    endif()
  endforeach()

  if(ARG_C)
    list(APPEND ARG_INSEXTS ".h")
  endif()
  if(ARG_CPP)
    list(APPEND ARG_INSEXTS ".H" ".h++" ".hh" ".hpp" ".hxx" ".inl")
  endif()
  foreach(ext ${ARG_INSEXTS})
    if(NOT ext MATCHES "^([.][^ \"%*./:<>?\\|]+)+$")
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
