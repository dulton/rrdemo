# ./clib/src
string(REPLACE "-" "__" exports "${PRJUPR}")
string(CONCAT exports "-D" "${exports}" "__EXPORTS")
add_definitions(${exports})

if(MSVC)
  add_compile_options("/wd4819")  # character cannot be represented
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
sources_helper(GENERATE INSTALL RECURSE C
  SRCVAR ${PRJUPR}_SRC)

option(${PRJUPR}_COMPILE_STATIC "Build static library." ON)
if(${PRJUPR}_COMPILE_STATIC)
  add_library(${PRJLWR}_static STATIC ${${PRJUPR}_SRC})
  set_target_properties(${PRJLWR}_static PROPERTIES
    C_STANDARD 11 C_STANDARD_REQUIRED ON
    OUTPUT_NAME "${PROJECT_NAME}" CLEAN_DIRECT_OUTPUT ON)
  install(TARGETS ${PRJLWR}_static DESTINATION "lib")
endif()

option(${PRJUPR}_COMPILE_SHARED "Build shared library." ON)
if(${PRJUPR}_COMPILE_STATIC)
  add_library(${PRJLWR}_shared SHARED ${${PRJUPR}_SRC})
  set_target_properties(${PRJLWR}_shared PROPERTIES
    C_STANDARD 11 C_STANDARD_REQUIRED ON
    OUTPUT_NAME "${PROJECT_NAME}" CLEAN_DIRECT_OUTPUT ON
    VERSION "${PROJECT_VERSION}" SOVERSION "${PROJECT_VERSION}")
  install(TARGETS ${PRJLWR}_shared DESTINATION "lib")
endif()
