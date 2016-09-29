#-------------------------------------------------------------------------------
# ./exe/src
#-------------------------------------------------------------------------------
# SRC
source_helper(GENERATE RECURSE C
              SRCVAR ${PRJUPR}_SRC)

option(${PRJUPR}_COMPILE_EXE ON)
if(${PRJUPR}_COMPILE_EXE)
   add_executable(${prjlwr}_exe ${${PRJUPR}_SRC})
   set_target_properties(${prjlwr}_exe
                         PROPERTIES
                         OUTPUT_NAME "${PROJECT_NAME}" CLEAN_DIRECT_OUTPUT ON)
   install(TARGETS ${prjlwr}_exe DESTINATION "bin")
endif()
