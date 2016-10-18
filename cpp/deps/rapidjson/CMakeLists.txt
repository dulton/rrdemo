#==============================================================================#
# \brief RapidJSON
# \author THL A29 Limited, a Tencent company, and Milo Yip. (the project)
# \author zhengrr (the file)
# \date 2016-7-20 – 10-18
# \copyright The MIT License
#==============================================================================#
cmake_minimum_required(VERSION 3.0)
project("RapidJSON"  VERSION 1.0.2  LANGUAGES CXX)
rrdemo_make_project_extra_variables()

set(default "${PROJECT_SOURCE_DIR}/rapidjson")
if(NOT EXISTS ${default})
   set(default "")
endif()
set(${PROJECT_NAME}_DIR ${default}  CACHE PATH "RapidJSON directory path.")
if(NOT EXISTS ${${PROJECT_NAME}_DIR})
   message(FATAL_ERROR "The 'RapidJSON directory' doesn't exist..")
endif()

set(${PROJECT_NAME}_INCLUDE "${PROJECT_NAME}_DIR/include")
