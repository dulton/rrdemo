#-------------------------------------------------------------------------------
# RrDemo-C/DemoExe/doxygen
#-------------------------------------------------------------------------------
find_package(Doxygen)
option(${PROJECT_NAME_UPPER}_GEN_DEV_DOC
       "Generate developing documentation (requires Doxygen)." ${DOXYGEN_FOUND})
if(${PROJECT_NAME_UPPER}_GEN_DEV_DOC)
   if(NOT DOXYGEN_FOUND)
      message(FATAL_ERROR "Doxygen is needed to generate the developing "
                          "documentation.")
   endif()

   set(doxyfile_in "${PROJECT_SOURCE_DIR}/doxygen/Doxyfile.in")
   set(doxyfile    "${PROJECT_BINARY_DIR}/doxygen/Doxyfile")
   configure_file(${doxyfile_in} ${doxyfile} @ONLY)

   list(APPEND ${PROJECT_NAME_UPPER}_DOC ${doxyfile_in})
   source_group("Source" FILES ${doxyfile_in})

   file(GLOB src "*.h")
   list(APPEND ${PROJECT_NAME_UPPER}_DOC ${src})
   source_group("Source" FILES ${src})

   add_custom_target(${PROJECT_NAME_LOWER}_dev_doc
                     COMMAND "${DOXYGEN_EXECUTABLE}" "${doxyfile}"
                     WORKING_DIRECTORY "${PROJECT_BINARY_DIR}"
                     COMMENT "Generating developing documentation with Doxygen."
                     VERBATIM
                     SOURCES ${${PROJECT_NAME_UPPER}_DOC})
   install(DIRECTORY "${PROJECT_BINARY_DIR}/docs/"  DESTINATION "docs")

endif()
