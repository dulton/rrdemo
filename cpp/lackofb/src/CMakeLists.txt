#-------------------------------------------------------------------------------
# rrdemo-cpp/lackofb/src
#-------------------------------------------------------------------------------
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
file(GLOB src_root "*.hpp" ".inl" "*.cpp")
list(APPEND ${pupr}_SRC ${src_root})
source_group("Source" FILES ${src_root})

# EXE
option(${pupr}_COMPILE_EXE "Build executable." ON)
if(${pupr}_COMPILE_EXE)
   add_executable(${plwr}_exe ${${pupr}_SRC})
   set_target_properties(${plwr}_exe PROPERTIES
                         OUTPUT_NAME "${pnom}"  CLEAN_DIRECT_OUTPUT ON)
   install(TARGETS ${plwr}_exe  DESTINATION "bin")
endif()
