# RrDemo › C Dom › CPP Exe
# zhengrr
# 2016-8-1 – 10-27
# The MIT License
cmake_minimum_required(VERSION 3.0)
project("${PRODUCT_NAME}-CPPExe" VERSION 0.0.0.0 LANGUAGES CXX)
make_project_extra_variables()

enable_unicode_support()

add_subdirectory("src")
add_subdirectory("test")
add_subdirectory("doxygen")
