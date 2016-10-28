# RrDemo › C Dom › Qt
# zhengrr
# 2016-6-28 – 10-27
# The MIT License
cmake_minimum_required(VERSION 3.0)
project("${PRODUCT_NAME}-Qt" LANGUAGES CXX)
make_project_extra_variables()

enable_unicode_support()

find_package(Qt5CMake)
if(QT5CMAKE_FOUND)
  add_subdirectory("src")
endif()
