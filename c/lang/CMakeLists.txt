#-------------------------------------------------------------------------------
# ./exe
#-------------------------------------------------------------------------------
# \author zhengrr
# \date 2016-8-1 – 9-30
# \copyright The MIT License
#-------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.0)
project("RrDemo-C-Exe" VERSION 0.0.0.0 LANGUAGES C)
rrdemo_make_project_extra_variables()

rrdemo_enable_unicode_support()

add_subdirectory("src")
add_subdirectory("test")
add_subdirectory("doxygen")
