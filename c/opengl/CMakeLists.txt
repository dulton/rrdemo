#==============================================================================#
# \brief RrDemo › C › OpenGL
# \author zhengrr
# \date 2016-10-12
# \copyright The MIT License
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
