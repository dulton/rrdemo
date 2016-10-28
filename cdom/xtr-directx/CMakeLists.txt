# RrDemo › C Dom › DirectX
# zhengrr
# 2016-10-13 – 27
# The MIT License
cmake_minimum_required(VERSION 3.0)
project("${PRODUCT_NAME}-DirectX" LANGUAGES CXX)
make_project_extra_variables()

enable_unicode_support()

add_subdirectory("src")
