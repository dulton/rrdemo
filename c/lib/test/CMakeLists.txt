#-------------------------------------------------------------------------------
# RrDemo-C-Lib/test
#-------------------------------------------------------------------------------
set(CHECK_INSTALL_DIR ""  CACHE PATH "Check directory path.")

find_package(Check)
option(${PROJECT_NAME_UPPER}_UNIT_TESTING
       "Enable unit testing (requires Check)." ${CHECK_FOUND})
if(${PROJECT_NAME_UPPER}_UNIT_TESTING)
   if(NOT CHECK_FOUND)
      message(FATAL_ERROR "Check is needed to Enable unit testing.")
   endif()
   
   include_directories("${CHECK_INCLUDE_DIR}")
   include_directories("${PROJECT_SOURCE_DIR}/src")
   
   # SRC
   source_helper(RECURSE C  SRCVAR ${PROJECT_NAME_UPPER}_TEST)
   
   # EXE
   add_executable(${PROJECT_NAME_LOWER}_test ${${PROJECT_NAME_UPPER}_TEST})
   target_link_libraries(${PROJECT_NAME_LOWER}_test ${CHECK_LIBRARIES})
   set_target_properties(${PROJECT_NAME_LOWER}_test PROPERTIES
                         OUTPUT_NAME "${PROJECT_NAME}_test"  CLEAN_DIRECT_OUTPUT ON)
   
   # CTest
   enable_testing()
   add_test("${PROJECT_NAME_LOWER}_test" "${PROJECT_NAME_LOWER}_test")
endif()
