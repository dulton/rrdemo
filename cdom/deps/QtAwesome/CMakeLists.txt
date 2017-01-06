#==============================================================================#
# \brief QtAwesome
# \author Rick Blommers (the project)
# \author zhengrr (the file)
# \date 2016-5-3 – 10-18
# \copyright The MIT License
#==============================================================================#
cmake_minimum_required(VERSION 3.0)
project("QtAwesome" VERSION 4.6.1 LANGUAGES CXX)
rrdemo_make_project_extra_variables()

rrdemo_enable_unicode_support()

rrdemo_find_qtdir()
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)

set(default "${PROJECT_SOURCE_DIR}/QtAwesome")
if(NOT EXISTS ${default})
   set(default "")
endif()
set(${PRJUPR}_DIR ${default} CACHE PATH "QtAwesome directory path.")
if(NOT EXISTS ${${PRJUPR}_DIR})
   message(FATAL_ERROR "The 'QtAwesome directory' doesn't exist.")
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
rrdemo_sources(SRCVAR ${PRJUPR}_SRC
               SRCDIR "QtAwesome"
               GRPDIR "deps\\QtAwesome"
               SRCEXTS ".h" ".cpp" ".qrc")

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
