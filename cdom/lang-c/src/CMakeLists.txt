# ./c/src
find_package(SGLIB)
if(SGLIB_FOUND)
  add_definitions("-DSGLIB")
  include_directories(${SGLIB_INCLUDE_DIRS})
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
sources_helper(GENERATE RECURSE C
  SRCVAR ${PRJUPR}_SRC)

option(${PRJUPR}_COMPILE_EXE "Build executable file." ON)
if(${PRJUPR}_COMPILE_EXE)
  add_executable(${PRJLWR}_exe ${${PRJUPR}_SRC})
  set_target_properties(${PRJLWR}_exe PROPERTIES
    C_STANDARD 11 C_STANDARD_REQUIRED ON
    OUTPUT_NAME "${PROJECT_NAME}" CLEAN_DIRECT_OUTPUT ON)
  install(TARGETS ${PRJLWR}_exe DESTINATION "bin")
endif()
