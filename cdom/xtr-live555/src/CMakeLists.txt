# ./live555/src
find_package(LIVE555 REQUIRED)
if(WIN32)
  set(${PRJUPR}_SOCKET_LIBRARIES "ws2_32.lib")
endif()

include_directories(${LIVE555_INCLUDE_DIRS})
set(CMAKE_INCLUDE_CURRENT_DIR ON)
sources_helper(GENERATE RECURSE CPP
  SRCVAR ${PRJUPR}_SRC)

option(${PRJUPR}_COMPILE_EXE "Build executable file." ON)
if(${PRJUPR}_COMPILE_EXE)
  add_executable(${PRJLWR}_exe ${${PRJUPR}_SRC})
  target_link_libraries(${PRJLWR}_exe rrdemo-cdom-cpp_library_static)  # link
  target_link_libraries(${PRJLWR}_exe ${LIVE555_LIBRARIES} ${${PRJUPR}_SOCKET_LIBRARIES})
  set_target_properties(${PRJLWR}_exe PROPERTIES
    CXX_STANDARD 14 CXX_STANDARD_REQUIRED ON
    OUTPUT_NAME "${PROJECT_NAME}" CLEAN_DIRECT_OUTPUT ON)
  install(TARGETS ${PRJLWR}_exe DESTINATION "bin")
endif()
