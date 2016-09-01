#-------------------------------------------------------------------------------
# RrDemo-C-Lib/doxygen
#-------------------------------------------------------------------------------
find_package(Doxygen)
option(${PROJECT_NAME_UPPER}_GEN_API_DOC
       "Generate API documentation (requires Doxygen)." ${DOXYGEN_FOUND})
if(${PROJECT_NAME_UPPER}_GEN_API_DOC)
   if(NOT DOXYGEN_FOUND)
      message(FATAL_ERROR "Doxygen is needed to generate the API "
                          "documentation.")
   endif()

   set(doxyfile_in "${PROJECT_SOURCE_DIR}/doxygen/Doxyfile.in")
   set(doxyfile    "${PROJECT_BINARY_DIR}/doxygen/Doxyfile")
   configure_file(${doxyfile_in} ${doxyfile} @ONLY)

   list(APPEND ${PROJECT_NAME_UPPER}_DOC ${doxyfile_in})
   source_group("Source" FILES ${doxyfile_in})

   file(GLOB src_root "*.h")
   list(APPEND ${PROJECT_NAME_UPPER}_DOC ${src_root})
   source_group("Source" FILES ${src_root})

   file(GLOB src_stdlib "stdlib/*.h")
   list(APPEND ${PROJECT_NAME_UPPER}_DOC ${src_stdlib})
   source_group("Source\\Standard Library" FILES ${src_stdlib})

   add_custom_target(${PROJECT_NAME_LOWER}_api_doc
                     COMMAND "${DOXYGEN_EXECUTABLE}" "${doxyfile}"
                     WORKING_DIRECTORY "${PROJECT_BINARY_DIR}"
                     COMMENT "Generating API documentation with Doxygen."
                     VERBATIM
                     SOURCES ${${PROJECT_NAME_UPPER}_DOC})
   install(DIRECTORY "${PROJECT_BINARY_DIR}/docs/"  DESTINATION "docs")

endif()
