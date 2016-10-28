# RrDemo › C Dom › C
# zhengrr
# 2016-10-12 – 27
# The MIT License
cmake_minimum_required(VERSION 3.0)
project("${PRODUCT_NAME}-C" LANGUAGES C)
make_project_extra_variables()

enable_unicode_support()

add_subdirectory("src")
