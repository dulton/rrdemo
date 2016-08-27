#-------------------------------------------------------------------------------
# rrdemo-c/langc/test
#-------------------------------------------------------------------------------
set(CHECK_INSTALL_DIR ""  CACHE PATH "Check directory path.")

find_package(Check)
option(${pupr}_UNIT_TESTING
       "Enable unit testing (requires Check)." ${CHECK_FOUND})
if(${pupr}_UNIT_TESTING)
   if(NOT CHECK_FOUND)
      message(FATAL_ERROR "Check is needed to Enable unit testing.")
   endif()
   
   include_directories("${CHECK_INCLUDE_DIR}")
   include_directories("${psrc}/src")
   
   # SRC
   source_helper(RECURSE C  SRCVAR ${pupr}_TEST)
   
   # EXE
   add_executable(${plwr}_test ${${pupr}_TEST})
   target_link_libraries(${plwr}_test ${CHECK_LIBRARIES})
   set_target_properties(${plwr}_test PROPERTIES
                         OUTPUT_NAME "${pnom}_test"  CLEAN_DIRECT_OUTPUT ON)
   
   # CTest
   enable_testing()
   add_test("${plwr}_test" "${plwr}_test")
endif()
