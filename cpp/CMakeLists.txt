# RrDemo › C++
# zhengrr
# 2016-6-28 – 10-21
# The MIT License
cmake_minimum_required(VERSION 3.0)
project("RrDemo-CPP" VERSION 0.0.0.0 LANGUAGES CXX)

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

option(${PRODUCT_NAME}_ENABLE_PROJECT_DIRECTX "Enable project DirectX (requires DirectX)." OFF)
if(${PRODUCT_NAME}_ENABLE_PROJECT_DIRECTX)
  add_subdirectory("directx")
endif()

option(${PRODUCT_NAME}_ENABLE_PROJECT_LIVE555 "Enable project LIVE555 (requires LIVE555)." OFF)
if(${PRODUCT_NAME}_ENABLE_PROJECT_LIVE555)
  add_subdirectory("live555")
endif()

option(${PRODUCT_NAME}_ENABLE_PROJECT_WINDOWS "Enable project Windows (requires Windows)." OFF)
if(${PRODUCT_NAME}_ENABLE_PROJECT_WINDOWS)
  add_subdirectory("windows")
endif()

option(${PRODUCT_NAME}_ENABLE_PROJECT_QT "Enable project Qt (requires Qt5)." OFF)
if(${PRODUCT_NAME}_ENABLE_PROJECT_QT)
  add_subdirectory("qt")
endif()

install(DIRECTORY "docs" DESTINATION ".")
install(DIRECTORY "spls" DESTINATION ".")
install(FILES "license.txt" DESTINATION ".")
install(FILES "release_notes.txt" DESTINATION ".")
