# RrDemo › C Dom › OpenGL
# zhengrr
# 2016-10-12 – 10-27
# The MIT License
cmake_minimum_required(VERSION 3.0)
project("${PRODUCT_NAME}-OpenGL" LANGUAGES C)
make_project_extra_variables()

enable_unicode_support()

find_package(OPENGL)
find_package(GLUT)
if(OPENGL_FOUND AND GLUT_FOUND)
  add_subdirectory("src")
endif()
