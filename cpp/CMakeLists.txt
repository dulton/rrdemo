#-------------------------------------------------------------------------------
# RrDemo › C++
#-------------------------------------------------------------------------------
# \author zhengrr
# \date 2016-6-28 – 9-30
# \copyright The MIT License
#-------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.0)
project("RrDemo-CPP"  VERSION 0.0.0.0  LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../c/cmake/modules")
include("zrhlprs")

zr_make_product_vars()

zr_ena_highest_wlvl_spt()

add_subdirectory("deps")
add_subdirectory("lang")
add_subdirectory("lib")
add_subdirectory("exe")
add_subdirectory("spls")

add_subdirectory("qt")

install(DIRECTORY "docs"  DESTINATION ".")
install(DIRECTORY "spls"  DESTINATION ".")
install(FILES "license.txt"  DESTINATION ".")
install(FILES "release_notes.txt"  DESTINATION ".")
