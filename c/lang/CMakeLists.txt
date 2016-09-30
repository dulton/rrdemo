#-------------------------------------------------------------------------------
# ./lang
#-------------------------------------------------------------------------------
# \author zhengrr
# \date 2016-9-29 – 30
# \copyright The MIT License
#-------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.0)
project("RrDemo-C-Lang" LANGUAGES C)
zr_make_project_extvars()

zr_ena_unicode_spt()

include_directories("${PROJECT_SOURCE_DIR}")
zr_srchlpr(GENERATE RECURSE C
           SRCVAR ${PRJUPR}_SRC)

option(${PRJUPR}_COMPILE_EXE "Build executable file." ON)
if(${PRJUPR}_COMPILE_EXE)
   add_executable(${PRJLWR}_exe ${${PRJUPR}_SRC})
   set_target_properties(${PRJLWR}_exe PROPERTIES
                         OUTPUT_NAME "${PROJECT_NAME}" CLEAN_DIRECT_OUTPUT ON)
   install(TARGETS ${PRJLWR}_exe DESTINATION "bin")
endif()
