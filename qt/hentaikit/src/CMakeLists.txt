#-------------------------------------------------------------------------------
# rrdemo-cpp/hentaikit/src
#-------------------------------------------------------------------------------


set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC             ON)
set(CMAKE_AUTOUIC             ON)
set(CMAKE_AUTORCC             ON)

find_package(Qt5Core    REQUIRED)

find_package(Qt5Gui     REQUIRED)
find_package(Qt5Widgets REQUIRED)

find_package(Qt5Network    REQUIRED)
find_package(Qt5WebSockets REQUIRED)

find_package(Qt5LinguistTools REQUIRED)

# CONFIG.HPP
set(config_in "${psrc}/src/config.hpp.in")
set(config    "${pbin}/src/config.hpp")
configure_file(${config_in} ${config} @ONLY)

list(APPEND ${pupr}_SRC ${config_in})
source_group("Source" FILES ${config_in})

list(APPEND ${pupr}_SRC ${config})
source_group("Generated" FILES ${config})

# VERINFO.RC
if(MSVC)
   set(verinfo_in "${psrc}/src/pfm/verinfo.rc.in")
   set(verinfo    "${pbin}/src/pfm/verinfo.rc")
   configure_file(${verinfo_in} ${verinfo} @ONLY)

   list(APPEND ${pupr}_SRC ${verinfo_in})
   source_group("Source\\Platform" FILES ${verinfo_in})

   list(APPEND ${pupr}_SRC ${verinfo})
   source_group("Generated" FILES ${verinfo})
endif()

# SRC
file(GLOB src_root "*.hpp" "*.inl" "*.cpp")
source_group("Source" FILES ${src_root})
list(APPEND ${pupr}_SRC ${src_root})

file(GLOB src_res "res/*.qrc")
source_group("Source\\Resources" FILES ${src_res})
list(APPEND ${pupr}_SRC ${src_res})

file(GLOB src_tool "tool/*.hpp" "tool/*.cpp")
source_group("Source\\Tool" FILES ${src_tool})
list(APPEND ${pupr}_SRC ${src_tool})

file(GLOB src_ui "ui/*.ui" "ui/*.hpp" "ui/*.cpp")
source_group("Source\\UI" FILES ${src_ui})
list(APPEND ${pupr}_SRC ${src_ui})

set(src_ts "ts/en-US.ts")

# TRANSLATION
option(${pupr}_UPDATE_TRANSLATIONS "Update source translation *.ts" OFF)
if(${pupr}_UPDATE_TRANSLATIONS)
   qt5_create_translation(src_qm ${src_root} ${src_ui} ${src_ts})
else()
   qt5_add_translation(src_qm ${src_ts})
endif()
list(APPEND ${pupr}_SRC ${src_qm})

# EXE
option(${pupr}_COMPILE_EXE "Build executable." ON)
if(${pupr}_COMPILE_EXE)
   add_executable(${plwr}_exe WIN32 ${${pupr}_SRC})
   target_link_libraries(${plwr}_exe
                         Qt5::Core
                         Qt5::Gui Qt5::Widgets
                         Qt5::Network Qt5::WebSockets)
   set_target_properties(${plwr}_exe PROPERTIES
                         OUTPUT_NAME "${pnom}"  CLEAN_DIRECT_OUTPUT ON)
   install(TARGETS ${plwr}_exe  DESTINATION "bin")
endif()
