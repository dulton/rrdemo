#==============================================================================#
# RrDemo › C › Lib
# zhengrr
# 2016-8-1 – 10-12
# The MIT License
#==============================================================================#
cmake_minimum_required(VERSION 3.0)
project("RrDemo-C-Lib" VERSION 0.0.0.0 LANGUAGES C)
rrdemo_make_project_extra_variables()

rrdemo_enable_unicode_support()

add_subdirectory("src")
add_subdirectory("test")
add_subdirectory("doxygen")
