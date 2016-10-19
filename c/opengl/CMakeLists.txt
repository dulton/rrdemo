#==============================================================================#
# RrDemo › C › OpenGL
# zhengrr
# 2016-10-12
# The MIT License
#==============================================================================#
cmake_minimum_required(VERSION 3.0)
project("RrDemo-C-OpenGL" LANGUAGES C)
rrdemo_make_project_extra_variables()

rrdemo_enable_unicode_support()

find_package(OPENGL)
find_package(GLUT)
if(OPENGL_FOUND AND GLUT_FOUND)
   add_subdirectory("src")
endif()
