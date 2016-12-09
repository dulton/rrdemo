# RrDemo › Cdom › Qt
# zhengrr
# 2016-6-28 – 12-9
# The MIT License
cmake_minimum_required(VERSION 3.0)
project("${PRODUCT_NAME}-Qt" LANGUAGES CXX)
make_project_extra_variables()

find_package(Qt5CMake)
if(QT5CMAKE_FOUND)
  add_subdirectory("src")
endif()
