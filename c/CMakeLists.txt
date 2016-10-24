# RrDemo › C
# zhengrr
# 2016-6-28 – 10-21
# The MIT License
cmake_minimum_required(VERSION 3.0)
project("RrDemo-C" VERSION 0.0.0.0 LANGUAGES C)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules")
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

option(${PRODUCT_NAME_UPPER}_ENABLE_PROJECT_FFMPEG "Enable project FFmpeg (requires FFmpeg)." OFF)
if(${PRODUCT_NAME}_ENABLE_PROJECT_FFMPEG)
  add_subdirectory("ffmpeg")
endif()

option(${PRODUCT_NAME_UPPER}_ENABLE_PROJECT_LINUX "Enable project Linux (requires Linux)." OFF)
if(${PRODUCT_NAME}_ENABLE_PROJECT_LINUX)
  add_subdirectory("linux")
endif()

option(${PRODUCT_NAME_UPPER}_ENABLE_PROJECT_OPENGL "Enable project OpenGL (requires OpenGL)." OFF)
if(${PRODUCT_NAME}_ENABLE_PROJECT_OPENGL)
  add_subdirectory("opengl")
endif()

install(DIRECTORY "docs" DESTINATION ".")
install(DIRECTORY "spls" DESTINATION ".")
install(FILES "license.txt" DESTINATION ".")
install(FILES "release_notes.txt" DESTINATION ".")
