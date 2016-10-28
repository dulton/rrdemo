# RrDemo › C Dom › C++
# zhengrr
# 2016-10-13 – 25
# The MIT License
cmake_minimum_required(VERSION 3.0)
project("${PRODUCT_NAME}-CPP" LANGUAGES CXX)
make_project_extra_variables()

enable_unicode_support()

add_subdirectory("src")
