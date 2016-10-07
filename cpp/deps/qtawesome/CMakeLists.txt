#-------------------------------------------------------------------------------
#       o@@o   @@   o@@o
#     o@  @o  @@  o@@@@o
#    @@  @@  @@  @@  @@ @@   @@ o@@@* o@@@  *@@@* @*@*@@* o@@@*
#   @@  @@ @@@@ @@  @@ @@   @@ @@ @@ @@    @@ @@ @@@@@@@ @@ @@
#  @@  @@  @@  @@@@@@ @@ @ @@ @@@@@ *@@@* @@ @@ @@ @ @@ @@@@@
# o@  @o  @@  @@  @@ @@ @ @@ @@       @@ @@ @@ @@ @ @@ @@
# o@@o@@ o@@ @@  @@ o@@o@@o *@@@@ @@@@o *@@@* @@ @ @@ *@@@@
#-------------------------------------------------------------------------------
# \author    the Proj: Rick Blommers
#            the File: zhengrr
# \date      2016-5-3 ~ 7-20
# \copyright The MIT License
#-------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.0)
project("QtAwesome"  VERSION 4.6.1  LANGUAGES CXX)

if(WIN32)
   add_definitions("-DUNICODE" "-D_UNICODE")
endif()

include("append_qtdir_to_prefixes")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC             ON)
set(CMAKE_AUTORCC             ON)

find_package(Qt5Core    REQUIRED)
find_package(Qt5Gui     REQUIRED)
find_package(Qt5Widgets REQUIRED)

set(default "${PROJECT_SOURCE_DIR}/QtAwesome")
if(NOT EXISTS ${default})
   set(default "")
endif()
set(${PROJECT_NAME}_DIR ${default}  CACHE PATH "QtAwesome directory path.")
if(NOT EXISTS ${${PROJECT_NAME}_DIR})
   message(FATAL_ERROR "The 'QtAwesome directory' doesn't exist.")
endif()

file(GLOB ${PROJECT_NAME}_SRC
   "${${PROJECT_NAME}_DIR}/QtAwesome/*.h"
   "${${PROJECT_NAME}_DIR}/QtAwesome/*.cpp"
   "${${PROJECT_NAME}_DIR}/QtAwesome/*.qrc")

add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_SRC})
target_link_libraries(${PROJECT_NAME}
   Qt5::Core
   Qt5::Gui Qt5::Widgets)
