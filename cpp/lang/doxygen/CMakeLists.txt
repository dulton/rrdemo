#-------------------------------------------------------------------------------
# rrdemo-cpp/langcpp/doxygen
#-------------------------------------------------------------------------------
find_package(Doxygen)
option(${pupr}_GEN_API_DOC
       "Generate API documentation (requires Doxygen)." ${DOXYGEN_FOUND})
if(${pupr}_GEN_API_DOC)
   if(NOT DOXYGEN_FOUND)
      message(FATAL_ERROR "Doxygen is needed to generate the API "
                          "documentation.")
   endif()

   set(doxyfile_in "${psrc}/doxygen/Doxyfile.in")
   set(doxyfile    "${pbin}/doxygen/Doxyfile")
   configure_file(${doxyfile_in} ${doxyfile} @ONLY)

   list(APPEND ${pupr}_DOC ${doxyfile_in})
   source_group("Source" FILES ${doxyfile_in})

   file(GLOB src "*.hpp")
   list(APPEND ${pupr}_DOC ${src})
   source_group("Source" FILES ${src})

   add_custom_target(${plwr}_api_doc
                     COMMAND "${DOXYGEN_EXECUTABLE}" "${doxyfile}"
                     WORKING_DIRECTORY "${pbin}"
                     COMMENT "Generating API documentation with Doxygen."
                     VERBATIM
                     SOURCES ${${pupr}_DOC})
   install(DIRECTORY "${pbin}/docs/"  DESTINATION "docs")

endif()
