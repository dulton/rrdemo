# ./tpty-opengl/src
find_package(OPENGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIR})

set(CMAKE_INCLUDE_CURRENT_DIR ON)
rrdemo_sources(GENERATE RECURSE C
  SRCVAR ${PRJUPR}_SRC)

add_executable(${PRJLWR}_exe ${${PRJUPR}_SRC})
target_link_libraries(${PRJLWR}_exe
  ${OPENGL_LIBRARIES}
  ${GLUT_LIBRARIES})
set_target_properties(${PRJLWR}_exe PROPERTIES
  C_STANDARD 11 C_STANDARD_REQUIRED ON
  OUTPUT_NAME "${PROJECT_NAME}" CLEAN_DIRECT_OUTPUT ON)
install(TARGETS ${PRJLWR}_exe DESTINATION "bin")
