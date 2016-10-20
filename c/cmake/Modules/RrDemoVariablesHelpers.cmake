# zhengrr
# 2016-10-8 – 20
# The MIT License

#[======================================================================[.rst:
RrDemo Variables Helpers
------------------------



Introduction
^^^^^^^^^^^^

Some variables set for RrDemo.

Module Function/Macros
^^^^^^^^^^^^^^^^^^^^^^
#]======================================================================]

#[==================================================[.rst:
.. command:: rrdemo_make_project_extra_variables

  This macro defines the following values:

  ::

    PROJECT_NAME_UPPER
    PROJECT_NAME_LOWER
    PRJUPR
    PRJLWR
#]==================================================]
macro(rrdemo_make_project_extra_variables)
  string(TOUPPER "${PROJECT_NAME}" PROJECT_NAME_UPPER)
  string(TOLOWER "${PROJECT_NAME}" PROJECT_NAME_LOWER)
  set(PRJUPR "${PROJECT_NAME_UPPER}")
  set(PRJLWR "${PROJECT_NAME_LOWER}")
endmacro()

#[==================================================[.rst:
.. command:: rrdemo_make_product_variables

  This macro defines the following values:

  ::

    PRODUCT_NAME
    PRODUCT_NAME_UPPER
    PRODUCT_NAME_LOWER
    PRODUCT_SOURCE_DIR
    PRODUCT_BINARY_DIR
    PRODUCT_VERSION
    PRODUCT_VERSION_MAJRO
    PRODUCT_VERSION_MINOR
    PRODUCT_VERSION_PATCH
    PRODUCT_VERSION_TWEAK
#]==================================================]
macro(rrdemo_make_product_variables)
  set(PRODUCT_NAME "${PROJECT_NAME}")
  string(TOUPPER "${PROJECT_NAME}" PRODUCT_NAME_UPPER)
  string(TOLOWER "${PROJECT_NAME}" PRODUCT_NAME_LOWER)
  set(PRODUCT_SOURCE_DIR "${PROJECT_SOURCE_DIR}")
  set(PRODUCT_BINARY_DIR "${PROJECT_BINARY_DIR}")
  set(PRODUCT_VERSION "${PROJECT_VERSION}")
  set(PRODUCT_VERSION_MAJRO "${PROJECT_VERSION_MAJOR}")
  set(PRODUCT_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
  set(PRODUCT_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
  set(PRODUCT_VERSION_TWEAK "${PROJECT_VERSION_TWEAK}")
endmacro()
