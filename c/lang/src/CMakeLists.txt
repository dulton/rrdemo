#------------------------------------------------------------------------------#
# ./lang/src
#------------------------------------------------------------------------------#
string(REPLACE "-" "_" exports "${PRJUPR}")
string(CONCAT exports "-D" "${exports}" "_EXPORTS")
add_definitions(${exports})

set(CMAKE_INCLUDE_CURRENT_DIR ON)
rrdemo_sources(GENERATE INSTALL RECURSE C
               SRCVAR ${PRJUPR}_SRC)

option(${PRJUPR}_COMPILE_STATIC "Build static library." ON)
if(${PRJUPR}_COMPILE_STATIC)
   add_library(${PRJLWR}_static STATIC ${${PRJUPR}_SRC})
   set_target_properties(${PRJLWR}_static PROPERTIES
                         OUTPUT_NAME "${PROJECT_NAME}" CLEAN_DIRECT_OUTPUT ON)
   install(TARGETS ${PRJLWR}_static DESTINATION "lib")
endif()

option(${PRJUPR}_COMPILE_SHARED "Build shared library." ON)
if(${PRJUPR}_COMPILE_STATIC)
   add_library(${PRJLWR}_shared SHARED ${${PRJUPR}_SRC})
   set_target_properties(${PRJLWR}_shared PROPERTIES
                         C_STANDARD 11 C_STANDARD_REQUIRED ON
                         OUTPUT_NAME "${PROJECT_NAME}" CLEAN_DIRECT_OUTPUT ON
                         VERSION "${PROJECT_VERSION}")
   install(TARGETS ${PRJLWR}_shared DESTINATION "lib")
endif()
