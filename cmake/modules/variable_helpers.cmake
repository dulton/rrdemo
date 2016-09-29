#-------------------------------------------------------------------------------
# VARIABLE HELPERS
#-------------------------------------------------------------------------------
# \author zhengrr
# \date 2016-9-28 – 29
# \copyright The MIT License
#-------------------------------------------------------------------------------

#-----------------------------------------------------------
# \since 2016-9-29
#-----------------------------------------------------------
macro(define_extra_variables_for_project)
   string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_UPPER)
   string(TOLOWER ${PROJECT_NAME} PROJECT_NAME_LOWER)
endmacro()

#-----------------------------------------------------------
# \since 2016-9-29
#-----------------------------------------------------------
macro(define_variables_for_product)
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
