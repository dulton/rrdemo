#-------------------------------------------------------------------------------
# ./exe/src
#-------------------------------------------------------------------------------
include_directories("${PROJECT_SOURCE_DIR}/src")
zr_srchlpr(GENERATE RECURSE CPP
           SRCVAR ${PRJUPR}_SRC)

option(${PRJUPR}_COMPILE_EXE "Build executable." ON)
if(${PRJUPR}_COMPILE_EXE)
   add_executable(${PRJLWR}_exe ${${PRJUPR}_SRC})
   set_target_properties(${PRJLWR}_exe PROPERTIES
                         OUTPUT_NAME "${PROJECT_NAME}" CLEAN_DIRECT_OUTPUT ON)
   install(TARGETS ${PRJLWR}_exe DESTINATION "bin")
endif()
