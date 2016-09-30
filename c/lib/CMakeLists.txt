#-------------------------------------------------------------------------------
# ./lib
#-------------------------------------------------------------------------------
# \author zhengrr
# \date 2016-8-1 – 9-30
# \copyright The MIT License
#-------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.0)
project("RrDemo-C-Lib" VERSION 0.0.0.0 LANGUAGES C)
zr_make_project_extvars()

zr_ena_unicode_spt()

add_subdirectory("src")
add_subdirectory("test")
add_subdirectory("doxygen")
