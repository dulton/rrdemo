# RrDemo › C++ › Qt
# zhengrr
# 2016-6-28 – 10-21
# The MIT License
cmake_minimum_required(VERSION 3.0)
project("RrDemo-CPP-Qt" LANGUAGES CXX)
rrdemo_make_project_extra_variables()

rrdemo_enable_unicode_support()

find_package(Qt5CMake)
if(QT5CMAKE_FOUND)
  add_subdirectory("src")
endif()
