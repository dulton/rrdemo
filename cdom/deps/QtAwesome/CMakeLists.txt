# zhengrr
# 2016-5-3 – 2017-1-7
# The MIT License

#[======================================================================[.rst:
QtAwesome
---------

Unofficial QtAwesome CMakeLists.
#]======================================================================]
cmake_minimum_required(VERSION 3.0)
project("QtAwesome" VERSION 4.6.1 LANGUAGES CXX)
make_project_extra_variables()

find_package(Qt5CMake REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
sources_helper(CPP QT
  SRCVAR ${PRJUPR}_SRC)

add_library(${PRJLWR}_static STATIC ${${PRJUPR}_SRC})
target_link_libraries(${PRJLWR}_static
  Qt5::Core Qt5::Gui Qt5::Widgets)
set_target_properties(${PRJLWR}_static PROPERTIES
  OUTPUT_NAME "${PROJECT_NAME}" CLEAN_DIRECT_OUTPUT ON
  AUTOMOC ON AUTORCC ON)
install(TARGETS ${PRJLWR}_static DESTINATION "dep")

add_library(${PRJLWR}_shared SHARED ${${PRJUPR}_SRC})
target_link_libraries(${PRJLWR}_shared
  Qt5::Core Qt5::Gui Qt5::Widgets)
set_target_properties(${PRJLWR}_shared PROPERTIES
  OUTPUT_NAME "${PROJECT_NAME}" CLEAN_DIRECT_OUTPUT ON
  VERSION "${PROJECT_VERSION}"
  AUTOMOC ON AUTORCC ON)
install(TARGETS ${PRJLWR}_shared DESTINATION "dep")
