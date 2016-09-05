#-------------------------------------------------------------------------------
# RrDemo-C-Lib/src
#-------------------------------------------------------------------------------
# -D{PRJ}_EXPORTS
string(CONCAT exports "-D" ${PROJECT_NAME_UPPER} "_EXPORTS")
add_definitions(${exports})

# SRC
include_directories("${PROJECT_SOURCE_DIR}/src")
include_directories("${PROJECT_BINARY_DIR}/src")
source_helper(GENERATE INSTALL RECURSE C
              SRCVAR ${PROJECT_NAME_UPPER}_SRC)

# STATIC LIB
option(${PROJECT_NAME_UPPER}_COMPILE_STATIC "Build static library." ON)
if(${PROJECT_NAME_UPPER}_COMPILE_STATIC)
   add_library(${PROJECT_NAME_LOWER}_static STATIC ${${PROJECT_NAME_UPPER}_SRC})
   set_target_properties(${PROJECT_NAME_LOWER}_static PROPERTIES
                         OUTPUT_NAME "${PROJECT_NAME}"  CLEAN_DIRECT_OUTPUT ON)
   install(TARGETS ${PROJECT_NAME_LOWER}_static  DESTINATION "lib")
endif()

# SHARED LIB
option(${PROJECT_NAME_UPPER}_COMPILE_SHARED "Build shared library." ON)
if(${PROJECT_NAME_UPPER}_COMPILE_STATIC)
   add_library(${PROJECT_NAME_LOWER}_shared SHARED ${${PROJECT_NAME_UPPER}_SRC})
   set_target_properties(${PROJECT_NAME_LOWER}_shared PROPERTIES
                         OUTPUT_NAME "${PROJECT_NAME}"  CLEAN_DIRECT_OUTPUT ON
                         VERSION "${PROJECT_VERSION}")
   install(TARGETS ${PROJECT_NAME_LOWER}_shared  DESTINATION "lib")
endif()
