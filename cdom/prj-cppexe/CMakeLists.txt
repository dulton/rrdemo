# RrDemo › Cdom › C++ Executable
# zhengrr
# 2016-8-1 – 2017-1-12
# The MIT License
cmake_minimum_required(VERSION 3.0)
project("${PRODUCT_NAME}-CPP_Executable" VERSION 0.0.0.0 LANGUAGES CXX)
make_project_extra_variables()

add_subdirectory("src")
add_subdirectory("test")
add_subdirectory("doxygen")
