# RrDemo › C++ › Qt
# zhengrr
# 2016-6-28 – 10-20
# The MIT License
cmake_minimum_required(VERSION 3.0)
project("RrDemo-CPP-Qt" LANGUAGES CXX)
rrdemo_make_project_extra_variables()

rrdemo_enable_unicode_support()

add_subdirectory("src")
