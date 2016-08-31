#-------------------------------------------------------------------------------
# RrDemo-C
#-------------------------------------------------------------------------------
# \author zhengrr
# \date 2016-6-28 ~ 8-31
# \copyright The MIT License
#-------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.0)
project("RrDemo-C"  VERSION 0.0.0.0  LANGUAGES C)

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

list(APPEND CMAKE_MODULE_PATH "${PRODUCT_SOURCE_DIR}/cmake")
include("compile_helpers")
include("source_helpers")

add_subdirectory("deps")
add_subdirectory("demolib")
add_subdirectory("demoexe")
add_subdirectory("spls")
install(DIRECTORY "docs"  DESTINATION ".")
install(DIRECTORY "spls"  DESTINATION ".")
install(FILES "license.txt"  DESTINATION ".")
install(FILES "release_notes.txt"  DESTINATION ".")
