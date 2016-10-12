#==============================================================================#
# \brief RrDemo › C › Lang
# \author zhengrr
# \date 2016-10-12
# \copyright The MIT License
#==============================================================================#
cmake_minimum_required(VERSION 3.0)
project("RrDemo-C-Lang" VERSION 0.0.0.0 LANGUAGES C)
rrdemo_make_project_extra_variables()

rrdemo_enable_unicode_support()

add_subdirectory("src")
