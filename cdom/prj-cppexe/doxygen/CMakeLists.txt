# ./cppexe/doxygen
find_package(Doxygen)
option(${PRJUPR}_GEN_DEV_DOC
  "Generate developing documentation (requires Doxygen)." ${DOXYGEN_FOUND})
if(${PRJUPR}_GEN_DEV_DOC)
  if(NOT DOXYGEN_FOUND)
    message(FATAL_ERROR "Doxygen is needed to generate the developing documentation.")
  endif()

  set(doxyfile_in "${PROJECT_SOURCE_DIR}/doxygen/Doxyfile.in")
  set(doxyfile "${PROJECT_BINARY_DIR}/doxygen/Doxyfile")
  configure_file(${doxyfile_in} ${doxyfile} @ONLY)

  list(APPEND ${PRJUPR}_DOC ${doxyfile_in})
  source_group("Source" FILES ${doxyfile_in})

  file(GLOB src "*.hpp")
  list(APPEND ${PRJUPR}_DOC ${src})
  source_group("Source" FILES ${src})

  add_custom_target(${PRJLWR}_dev_doc
    COMMAND "${DOXYGEN_EXECUTABLE}" "${doxyfile}"
    WORKING_DIRECTORY "${PROJECT_BINARY_DIR}"
    COMMENT "Generating developing documentation with Doxygen."
    VERBATIM
    SOURCES ${${PRJUPR}_DOC})
  install(DIRECTORY "${PROJECT_BINARY_DIR}/doxygen/docs/" DESTINATION "docs")
endif()
