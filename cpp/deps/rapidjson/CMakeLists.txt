#-------------------------------------------------------------------------------
#       @@@o                @@     @@   @@@ *@@@o *o@@o* @o  @@
#      @@ @@        @@@@*         @@    @@ @@  @ o@  @o @@o @@
#     @@ @@  @@@@* @@ @@ @@@     @@    @@ @@    @@  @@ @@@o@@
#    @@ @@     @@ @@ @@  @@  *@@@@    @@ *@@@* @@  @@ @@ @@@
#   @@@@* *@@@@@ @@@@*  @@  @@ @@ @@ @@    @@ @@  @@ @@  @@
#  @@ @@ @@  @@ @@     @@  @@ @@ @@o@@ @  @@ o@  @o @@  @@
# @@ @@ *@@@@@ @@    @@@@ *@@@@ *@@@* *@@@* *o@@o* @@  @@
#-------------------------------------------------------------------------------
# \author    the Proj: THL A29 Limited, a Tencent company, and Milo Yip.
#            the File: zhengrr
# \date      2016-7-20
# \copyright The MIT License
#-------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.0)
project("RapidJSON"  VERSION 1.0.2  LANGUAGES CXX)

set(default "${PROJECT_SOURCE_DIR}/rapidjson")
if(NOT EXISTS ${default})
   set(default "")
endif()
set(${PROJECT_NAME}_DIR ${default}  CACHE PATH "RapidJSON directory path.")
if(NOT EXISTS ${${PROJECT_NAME}_DIR})
   message(FATAL_ERROR "The 'RapidJSON directory' doesn't exist..")
endif()

set(${PROJECT_NAME}_INCLUDE "${PROJECT_NAME}_DIR/include")
