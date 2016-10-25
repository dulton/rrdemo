# RrDemo › C Family › DirectX
# zhengrr
# 2016-10-13 – 25
# The MIT License
cmake_minimum_required(VERSION 3.0)
project("RrDemo-CFamily-DirectX" LANGUAGES CXX)
rrdemo_make_project_extra_variables()

rrdemo_enable_unicode_support()

add_subdirectory("src")
