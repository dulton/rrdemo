# RrDemo › Cdom › LIVE555
# zhengrr
# 2016-10-18 – 12-9
# The MIT License
cmake_minimum_required(VERSION 3.0)
project("${PRODUCT_NAME}-LIVE555" LANGUAGES CXX)
make_project_extra_variables()

find_package(LIVE555)
if(LIVE555_FOUND)
  add_subdirectory("src")
endif()
