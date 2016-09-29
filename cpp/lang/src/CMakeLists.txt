#-------------------------------------------------------------------------------
# rrdemo-cpp/langcpp/src
#-------------------------------------------------------------------------------
# -D{PRJ}_EXPORTS
string(CONCAT exports "-D" ${pupr} "_EXPORTS")
add_definitions(${exports})

# CONFIG.HPP
set(config_in "${psrc}/src/config.hpp.in")
set(config    "${pbin}/src/config.hpp")
configure_file(${config_in} ${config} @ONLY)

list(APPEND ${pupr}_SRC ${config_in})
source_group("Source" FILES ${config_in})

list(APPEND ${pupr}_SRC ${config})
source_group("Generated" FILES ${config})

install(FILES ${config}  DESTINATION "include/${plwr}")

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
file(GLOB src_root "*.hpp" "*.inl" "*.npp" "*.cpp")

list(APPEND ${pupr}_SRC ${src_root})
source_group("Source" FILES ${src_root})
file(GLOB incl_root "*.hpp" "*.inl")
install(FILES ${incl_root}  DESTINATION "include/${plwr}")

file(GLOB src_dznptns "dznptns/*.hpp" "dznptns/*.inl" "dznptns/*.npp"
                      "dznptns/*.cpp")
list(APPEND ${pupr}_SRC ${src_dznptns})
source_group("Source\\Design Patterns" FILES ${src_dznptns})
file(GLOB incl_dznptns "dznptns/*.hpp" "dznptns/*.inl")
install(FILES ${incl_dznptns}  DESTINATION "include/${plwr}/dznptns")

file(GLOB src_json "json/*.hpp" "json/*.inl" "json/*.npp" "json/*.cpp")
list(APPEND ${pupr}_SRC ${src_json})
source_group("Source\\JSON" FILES ${src_json})
file(GLOB incl_json "json/*.hpp" "json/*.inl")
install(FILES ${incl_json}  DESTINATION "include/${plwr}/json")

file(GLOB src_stdlib "stdlib/*.hpp" "stdlib/*.inl" "stdlib/*.npp"
                     "stdlib/*.cpp")
list(APPEND ${pupr}_SRC ${src_stdlib})
source_group("Src\\Standard Library" FILES ${src_stdlib})
file(GLOB incl_stdlib "stdlib/*.hpp" "stdlib/*.inl")
install(FILES ${incl_stdlib}  DESTINATION "include/${plwr}/stdlib")

file(GLOB src_uncnv "uncnv/*.hpp" "uncnv/*.inl" "uncnv/*.npp" "uncnv/*.cpp")
list(APPEND ${pupr}_SRC ${src_uncnv})
source_group("Source\\Unit Conversion" FILES ${src_uncnv})
file(GLOB incl_uncnv "uncnv/*.hpp" "uncnv/*.inl")
install(FILES ${incl_uncnv}  DESTINATION "include/${plwr}/uncnv")

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
if(${pupr}_COMPILE_SHARED)
   add_library(${plwr}_shared SHARED ${${pupr}_SRC})
   set_target_properties(${plwr}_shared PROPERTIES
                         OUTPUT_NAME "${pnom}"  CLEAN_DIRECT_OUTPUT ON
                         VERSION "${pver}")
   install(TARGETS ${plwr}_shared  DESTINATION "lib")
endif()
