# RrDemo › C Dom
# zhengrr
# 2016-6-28 – 10-27
# The MIT License
cmake_minimum_required(VERSION 3.0)
project("RrDemo-CDom" VERSION 0.0.0.0)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules")
include("RrDemoVariablesHelpers")
include("RrDemoSupportsHelpers")
include("RrDemoSourcesHelpers")

rrdemo_make_product_variables()

rrdemo_enable_highest_warning_level_support()

add_subdirectory("deps")
add_subdirectory("prj-clib")
add_subdirectory("prj-cppexe")
add_subdirectory("spls")

add_subdirectory("lang-c")
add_subdirectory("lang-cpp")
#add_subdirectory("lang-go")
add_subdirectory("lang-lua")
#add_subdirectory("lang-rust")

add_subdirectory("xtr-boost")
add_subdirectory("xtr-directx")
add_subdirectory("xtr-linux")
add_subdirectory("xtr-live555")
add_subdirectory("xtr-opengl")
add_subdirectory("xtr-qt")
add_subdirectory("xtr-windows")

install(DIRECTORY "docs" DESTINATION ".")
install(DIRECTORY "spls" DESTINATION ".")
install(FILES "license.txt" DESTINATION ".")
install(FILES "release_notes.txt" DESTINATION ".")
