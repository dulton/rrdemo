#-------------------------------------------------------------------------------
# rrdemo-c/langc/src
#-------------------------------------------------------------------------------
# -D{PRJ}_EXPORTS
string(CONCAT exports "-D" ${pupr} "_EXPORTS")
add_definitions(${exports})

# SRC
include_directories("${psrc}/src")
include_directories("${pbin}/src")
source_helper(GENERATE INSTALL RECURSE C
              SRCVAR ${pupr}_SRC)

# STATIC LIB
option(${pupr}_COMPILE_STATIC "Build static library." ON)
if(${pupr}_COMPILE_STATIC)
   add_library(${plwr}_static STATIC ${${pupr}_SRC})
   set_target_properties(${plwr}_static PROPERTIES
                         OUTPUT_NAME "${pnom}"  CLEAN_DIRECT_OUTPUT ON)
   install(TARGETS ${plwr}_static  DESTINATION "lib")
endif()

# SHARED LIB
option(${pupr}_COMPILE_SHARED "Build shared library." ON)
if(${pupr}_COMPILE_STATIC)
   add_library(${plwr}_shared SHARED ${${pupr}_SRC})
   set_target_properties(${plwr}_shared PROPERTIES
                         OUTPUT_NAME "${pnom}"  CLEAN_DIRECT_OUTPUT ON
                         VERSION "${pver}")
   install(TARGETS ${plwr}_shared  DESTINATION "lib")
endif()
