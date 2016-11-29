# ./qt/src
find_package(Qt5CMake REQUIRED)

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5Qml REQUIRED)
find_package(Qt5Quick REQUIRED)
find_package(Qt5Sql REQUIRED)
find_package(Qt5WebSockets REQUIRED)
find_package(Qt5Widgets REQUIRED)

find_package(Qt5LinguistTools REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
sources_helper(GENERATE RECURSE CPP QT
  SRCVAR ${PRJUPR}_SRC)
set(${PRJUPR}_TS "ts/hans-CN.ts")

file(COPY "qml" DESTINATION ".")
install(DIRECTORY "qml" DESTINATION "bin/") 

option(${PRJUPR}_UPDATE_TRANSLATIONS "Update source translation *.ts" OFF)
if(${PRJUPR}_UPDATE_TRANSLATIONS)
  qt5_create_translation(${PRJUPR}_QM ${${PRJUPR}_SRC} ${${PRJUPR}_TS})
else()
  qt5_add_translation(${PRJUPR}_QM ${${PRJUPR}_TS})
endif()
file(COPY ${${PRJUPR}_QM} DESTINATION "${CMAKE_CURRENT_LIST_DIR}/rc/qm")

option(${PRJUPR}_COMPILE_EXE "Build executable file." ON)
if(${PRJUPR}_COMPILE_EXE)
  add_executable(${PRJLWR}_exe WIN32 ${${PRJUPR}_SRC})
  target_link_libraries(${PRJLWR}_exe
    Qt5::Core Qt5::Gui Qt5::Network Qt5::Qml Qt5::Quick Qt5::Sql Qt5::WebSockets
    Qt5::Widgets)
  set_target_properties(${PRJLWR}_exe PROPERTIES
    CXX_STANDARD 14 CXX_STANDARD_REQUIRED ON
    OUTPUT_NAME "${PROJECT_NAME}" CLEAN_DIRECT_OUTPUT ON
    AUTOMOC ON AUTOUIC ON AUTORCC ON)
  install(TARGETS ${PRJLWR}_exe DESTINATION "bin")
endif()
