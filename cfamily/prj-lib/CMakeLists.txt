# RrDemo › C Family › Lib
# zhengrr
# 2016-8-1 – 10-25
# The MIT License
cmake_minimum_required(VERSION 3.0)
project("RrDemo-CFamily-Lib" VERSION 0.0.0.0 LANGUAGES C CXX)
rrdemo_make_project_extra_variables()

rrdemo_enable_unicode_support()

add_subdirectory("src")
add_subdirectory("test")
add_subdirectory("doxygen")
