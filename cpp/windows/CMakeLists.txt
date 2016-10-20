# RrDemo › C++ › Windows
# zhengrr
# 2016-10-12 – 20
# The MIT License
cmake_minimum_required(VERSION 3.0)
project("RrDemo-CPP-Windows" LANGUAGES CXX)
rrdemo_make_project_extra_variables()

rrdemo_enable_unicode_support()

add_subdirectory("src")
