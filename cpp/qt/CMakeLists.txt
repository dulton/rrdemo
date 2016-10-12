#==============================================================================#
# \brief RrDemo › C++ › Qt
# \author zhengrr
# \date 2016-6-28 – 10-12
# \copyright The MIT License
#==============================================================================#
cmake_minimum_required(VERSION 3.0)
project("RrDemo-CPP-Qt"  VERSION 0.0.0.0  LANGUAGES CXX)
rrdemo_make_project_extra_variables()

rrdemo_enable_unicode_support()

add_subdirectory("src")
add_subdirectory("test")
add_subdirectory("doxygen")
