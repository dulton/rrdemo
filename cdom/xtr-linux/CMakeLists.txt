# RrDemo › C Dom › Linux
# zhengrr
# 2016-10-8 – 27
# The MIT License
cmake_minimum_required(VERSION 3.0)
project("RrDemo-CDom-Linux" LANGUAGES C)
rrdemo_make_project_extra_variables()

rrdemo_enable_unicode_support()

add_subdirectory("src")
