#==============================================================================#
# RrDemo › C › Linux
# zhengrr
# 2016-10-8 – 10-13
# The MIT License
#==============================================================================#
cmake_minimum_required(VERSION 3.0)
project("RrDemo-C-Linux" LANGUAGES C)
rrdemo_make_project_extra_variables()

rrdemo_enable_unicode_support()

add_subdirectory("src")
