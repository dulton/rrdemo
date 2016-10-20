# zhengrr
# 2016-10-3 – 20
# The MIT License

#[======================================================================[.rst:
Append QTDIR to Prefix
----------------------

Find & append ``QTDIR`` to ``CMAKE_PREFIX_PATH`` for using Qt5.

Module Function/Macros
^^^^^^^^^^^^^^^^^^^^^^
#]======================================================================]

#[==================================================[.rst:
.. command:: append_qtdir_to_prefix

  ::

    append_qtdir_to_prefix()

  This function will run automatically once.
#]==================================================]
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
