#==============================================================================#
# \file
# \brief RrDemo › C
# \author zhengrr
# \date 2016-6-28 – 10-9
# \copyright The MIT License
#==============================================================================#
cmake_minimum_required(VERSION 3.0)
project("RrDemo-C" VERSION 0.0.0.0 LANGUAGES C)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules")
include("RrDemoVariablesHelpers")
include("RrDemoSupportsHelpers")
include("RrDemoSourcesHelpers")

rrdemo_make_product_variables()

rrdemo_enable_highest_warning_level_support()

add_subdirectory("deps")
add_subdirectory("lang")
add_subdirectory("demo")
add_subdirectory("spls")

add_subdirectory("linux")

install(DIRECTORY "docs" DESTINATION ".")
install(DIRECTORY "spls" DESTINATION ".")
install(FILES "license.txt" DESTINATION ".")
install(FILES "release_notes.txt" DESTINATION ".")
