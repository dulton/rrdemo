# RrDemo › C Family
# zhengrr
# 2016-6-28 – 10-25
# The MIT License
cmake_minimum_required(VERSION 3.0)
project("RrDemo-CFamily" VERSION 0.0.0.0)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules")
include("RrDemoVariablesHelpers")
include("RrDemoSupportsHelpers")
include("RrDemoSourcesHelpers")

rrdemo_make_product_variables()

rrdemo_enable_highest_warning_level_support()

add_subdirectory("deps")
add_subdirectory("lang-c")
add_subdirectory("lang-cpp")
add_subdirectory("prj-lib")
add_subdirectory("prj-exe")
add_subdirectory("spls")
add_subdirectory("trdpty-directx")
add_subdirectory("trdpty-linux")
add_subdirectory("trdpty-live555")
add_subdirectory("trdpty-opengl")
add_subdirectory("trdpty-qt")
add_subdirectory("trdpty-windows")

install(DIRECTORY "docs" DESTINATION ".")
install(DIRECTORY "spls" DESTINATION ".")
install(FILES "license.txt" DESTINATION ".")
install(FILES "release_notes.txt" DESTINATION ".")
