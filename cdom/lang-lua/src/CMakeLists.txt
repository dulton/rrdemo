# ./lua/src
find_package(Lua REQUIRED)

include_directories(${LUA_INCLUDE_DIR})
set(CMAKE_INCLUDE_CURRENT_DIR ON)
sources_helper(GENERATE RECURSE C
  SRCVAR ${PRJUPR}_SRC)

option(${PRJUPR}_COMPILE_EXE "Build executable file." ON)
if(${PRJUPR}_COMPILE_EXE)
  add_executable(${PRJLWR}_exe ${${PRJUPR}_SRC})
  target_link_libraries(${PRJLWR}_exe ${LUA_LIBRARIES})
  set_target_properties(${PRJLWR}_exe PROPERTIES
    C_STANDARD 11 C_STANDARD_REQUIRED ON
    OUTPUT_NAME "${PROJECT_NAME}" CLEAN_DIRECT_OUTPUT ON)
  install(TARGETS ${PRJLWR}_exe DESTINATION "bin")
endif()
