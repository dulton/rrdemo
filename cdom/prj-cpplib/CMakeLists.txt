# RrDemo › Cdom › C++ Library
# zhengrr
# 2017-1-12
# The MIT License
cmake_minimum_required(VERSION 3.0)
project("${PRODUCT_NAME}-CPP_Library" VERSION 0.0.0.1 LANGUAGES CXX)
make_project_extra_variables()

add_subdirectory("src")
add_subdirectory("test")
add_subdirectory("doxygen")
