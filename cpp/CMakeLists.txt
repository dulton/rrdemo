#-------------------------------------------------------------------------------
# RrDemo–C++
#-------------------------------------------------------------------------------
# \author zhengrr
# \date 2016-6-28 ~ 8-4
# \copyright The MIT License
#-------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.0)
project("RRDemo-CPP"  VERSION 0.0.0.0  LANGUAGES CXX)

# Some global variables in product
set(PNOM ${PROJECT_NAME})              # product name
string(TOUPPER ${PROJECT_NAME} PUPR)   # product name upper
string(TOLOWER ${PROJECT_NAME} PLWR)   # product name lower
set(PSRC ${PROJECT_SOURCE_DIR})        # product source dir
set(PBIN ${PROJECT_BINARY_DIR})        # product binary dir
set(PVER ${PROJECT_VERSION})           # product version
set(PVERMJR ${PROJECT_VERSION_MAJOR})  # product version major
set(PVERMIN ${PROJECT_VERSION_MINOR})  # product version minor
set(PVERPCH ${PROJECT_VERSION_PATCH})  # product version patch
set(PVERTWK ${PROJECT_VERSION_TWEAK})  # product version tweak

list(APPEND CMAKE_MODULE_PATH "${PSRC}/cmake")
include("cpp_highest_warning_level")
include("append_qtdir_to_prefixes")

add_subdirectory("deps")
add_subdirectory("langcpp")
add_subdirectory("lackofb")
add_subdirectory("hentaikit")
add_subdirectory("spls")

install(DIRECTORY "docs"  DESTINATION ".")
install(DIRECTORY "spls"  DESTINATION ".")
install(FILES "license.txt"  DESTINATION ".")
install(FILES "release_notes.txt"  DESTINATION ".")
