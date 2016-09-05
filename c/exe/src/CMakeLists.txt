#-------------------------------------------------------------------------------
# RrDemo-C-Exe/src
#-------------------------------------------------------------------------------
# SRC
source_helper(GENERATE RECURSE C
              SRCVAR ${PROJECT_NAME_UPPER}_SRC)

# EXE
option(${PROJECT_NAME_UPPER}_COMPILE_EXE "Build executable." ON)
if(${PROJECT_NAME_UPPER}_COMPILE_EXE)
   add_executable(${PROJECT_NAME_LOWER}_exe ${${PROJECT_NAME_UPPER}_SRC})
   set_target_properties(${PROJECT_NAME_LOWER}_exe PROPERTIES
                         OUTPUT_NAME "${PROJECT_NAME}"  CLEAN_DIRECT_OUTPUT ON)
   install(TARGETS ${PROJECT_NAME_LOWER}_exe  DESTINATION "bin")
endif()
