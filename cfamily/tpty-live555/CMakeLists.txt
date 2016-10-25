# RrDemo › C Family › LIVE555
# zhengrr
# 2016-10-18 – 25
# The MIT License
cmake_minimum_required(VERSION 3.0)
project("RrDemo-CFamily-LIVE555" LANGUAGES CXX)
rrdemo_make_project_extra_variables()

rrdemo_enable_unicode_support()

find_package(LIVE555)
if(LIVE555_FOUND)
  add_subdirectory("src")
endif()
