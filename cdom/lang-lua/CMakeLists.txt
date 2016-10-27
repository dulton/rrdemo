# RrDemo › C Dom › Lua
# zhengrr
# 2016-10-27
# The MIT License
cmake_minimum_required(VERSION 3.0)
project("RrDemo-CDom-Lua" LANGUAGES C)
rrdemo_make_project_extra_variables()

rrdemo_enable_unicode_support()

find_package(Lua)
if(LUA_FOUND)
  add_subdirectory("src")
endif()
