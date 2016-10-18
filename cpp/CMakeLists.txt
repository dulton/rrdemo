#==============================================================================#
# \brief RrDemo › C++
# \author zhengrr
# \date 2016-6-28 – 10-12
# \copyright The MIT License
#==============================================================================#
cmake_minimum_required(VERSION 3.0)
project("RrDemo-CPP"  VERSION 0.0.0.0  LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../c/cmake/Modules")
include("RrDemoVariablesHelpers")
include("RrDemoSupportsHelpers")
include("RrDemoSourcesHelpers")

rrdemo_make_product_variables()

rrdemo_enable_highest_warning_level_support()

add_subdirectory("deps")
add_subdirectory("lib")
add_subdirectory("exe")
add_subdirectory("spls")

add_subdirectory("lang")

add_subdirectory("directx")
add_subdirectory("live555")
add_subdirectory("windows")
add_subdirectory("qt")

install(DIRECTORY "docs"  DESTINATION ".")
install(DIRECTORY "spls"  DESTINATION ".")
install(FILES "license.txt"  DESTINATION ".")
install(FILES "release_notes.txt"  DESTINATION ".")
