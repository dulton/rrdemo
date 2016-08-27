#-------------------------------------------------------------------------------
# rrdemo-c/logic01134/src
#-------------------------------------------------------------------------------
# SRC
source_helper(GENERATE RECURSE C
              SRCVAR ${pupr}_SRC)

# EXE
option(${pupr}_COMPILE_EXE "Build executable." ON)
if(${pupr}_COMPILE_EXE)
   add_executable(${plwr}_exe ${${pupr}_SRC})
   set_target_properties(${plwr}_exe PROPERTIES
                         OUTPUT_NAME "${pnom}"  CLEAN_DIRECT_OUTPUT ON)
   install(TARGETS ${plwr}_exe  DESTINATION "bin")
endif()
