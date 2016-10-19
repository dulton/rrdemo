#==============================================================================#
# RrDemo › C › Lang
# zhengrr
# 2016-10-12
# The MIT License
#==============================================================================#
cmake_minimum_required(VERSION 3.0)
project("RrDemo-C-Lang" LANGUAGES C)
rrdemo_make_project_extra_variables()

rrdemo_enable_unicode_support()

add_subdirectory("src")
