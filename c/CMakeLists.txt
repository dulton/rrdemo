#-------------------------------------------------------------------------------
# RrDemo › C
#-------------------------------------------------------------------------------
# \author zhengrr
# \date 2016-6-28 – 9-30
# \copyright The MIT License
#-------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.0)
project("RrDemo-C" VERSION 0.0.0.0 LANGUAGES C)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake/modules")
include("zrhlprs")

zr_make_product_vars()

zr_ena_highest_wlvl_spt()

add_subdirectory("deps")
add_subdirectory("lang")
add_subdirectory("lib")
add_subdirectory("exe")
add_subdirectory("spls")

install(DIRECTORY "docs" DESTINATION ".")
install(DIRECTORY "spls" DESTINATION ".")
install(FILES "license.txt" DESTINATION ".")
install(FILES "release_notes.txt" DESTINATION ".")
