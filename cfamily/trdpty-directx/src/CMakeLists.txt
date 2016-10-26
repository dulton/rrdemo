# ./trdpty-directx/src
set(CMAKE_INCLUDE_CURRENT_DIR ON)
rrdemo_sources(GENERATE RECURSE CPP
  SRCVAR ${PRJUPR}_SRC)

add_executable(${PRJLWR}_exe ${${PRJUPR}_SRC})
target_link_libraries(${PRJLWR}_exe
  d3d11 dxgi d3dcompiler)
set_target_properties(${PRJLWR}_exe PROPERTIES
  CXX_STANDARD 14 CXX_STANDARD_REQUIRED ON
  OUTPUT_NAME "${PROJECT_NAME}" CLEAN_DIRECT_OUTPUT ON)
install(TARGETS ${PRJLWR}_exe DESTINATION "bin")
