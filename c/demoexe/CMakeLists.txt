#-------------------------------------------------------------------------------
# RrDemo-C-DemoExe
#-------------------------------------------------------------------------------
# \author zhengrr
# \date 2016-8-1 ~ 9-1
# \copyright The MIT License
#-------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.0)
project("RrDemo-C-DemoExe"  VERSION 0.0.0.0  LANGUAGES C)

string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_UPPER)
string(TOLOWER ${PROJECT_NAME} PROJECT_NAME_LOWER)

if(WIN32)
   add_definitions("-DUNICODE" "-D_UNICODE")
endif()

add_subdirectory("src")
add_subdirectory("test")
add_subdirectory("doxygen")
