#-------------------------------------------------------------------------------
# rrdemo-c/logic01134/doxygen
#-------------------------------------------------------------------------------
find_package(Doxygen)
option(${pupr}_GEN_DEV_DOC
       "Generate developing documentation (requires Doxygen)." ${DOXYGEN_FOUND})
if(${pupr}_GEN_DEV_DOC)
   if(NOT DOXYGEN_FOUND)
      message(FATAL_ERROR "Doxygen is needed to generate the developing "
                          "documentation.")
   endif()

   set(doxyfile_in "${psrc}/doxygen/Doxyfile.in")
   set(doxyfile    "${pbin}/doxygen/Doxyfile")
   configure_file(${doxyfile_in} ${doxyfile} @ONLY)

   list(APPEND ${pupr}_DOC ${doxyfile_in})
   source_group("Source" FILES ${doxyfile_in})

   file(GLOB src "*.h")
   list(APPEND ${pupr}_DOC ${src})
   source_group("Source" FILES ${src})

   add_custom_target(${plwr}_dev_doc
                     COMMAND "${DOXYGEN_EXECUTABLE}" "${doxyfile}"
                     WORKING_DIRECTORY "${pbin}"
                     COMMENT "Generating developing documentation with Doxygen."
                     VERBATIM
                     SOURCES ${${pupr}_DOC})
   install(DIRECTORY "${pbin}/docs/"  DESTINATION "docs")

endif()
