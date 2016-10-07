#-------------------------------------------------------------------------------
# ./qt
#-------------------------------------------------------------------------------
# \author zhengrr
# \date 2016-6-28 – 10-3
# \copyright The MIT License
#-------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.0)
project("RrDemo-CPP-Qt"  VERSION 0.0.0.0  LANGUAGES CXX)
zr_make_project_extvars()

zr_ena_unicode_spt()

add_subdirectory("src")
add_subdirectory("test")
add_subdirectory("doxygen")
