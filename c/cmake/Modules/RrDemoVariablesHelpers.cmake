#==============================================================================#
# \file                                                                        #
# \brief RrDemo Variables Helpers                                              #
# \author zhengrr                                                              #
# \date 2016-10-8 – 10-9                                                       #
# \copyright The MIT License                                                   #
#==============================================================================#

#------------------------------------------------------------------------------#
# \brief Make Project Extra Variables                                          #
# \since 2016-9-30 – 10-8                                                      #
#------------------------------------------------------------------------------#
macro(rrdemo_make_project_extra_variables)
   string(TOUPPER "${PROJECT_NAME}" PROJECT_NAME_UPPER)
   string(TOLOWER "${PROJECT_NAME}" PROJECT_NAME_LOWER)
   set(PRJUPR "${PROJECT_NAME_UPPER}")
   set(PRJLWR "${PROJECT_NAME_LOWER}")
endmacro()

#------------------------------------------------------------------------------#
# \brief Make Product Variables                                                #
# \since 2016-9-30 – 10-8                                                      #
#------------------------------------------------------------------------------#
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
