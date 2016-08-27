#-------------------------------------------------------------------------------
#       @@                        *o@@@ @@@@* @@@@*
#      @@                  *@@@o @@o   @@ @@ @@ @@
#     @@    @@@@*  @*@@@* @@ @@ @@    @@ @@ @@ @@
#    @@        @@ @@@@@@ @@ @@ @@    @@ @@ @@ @@
#   @@    *@@@@@ @@  @@ *@@@@ @@    @@@@* @@@@*
#  @@    @@  @@ @@  @@    @@ @@o   @@    @@
# @@@@@ *@@@@@ @@  @@  @@@* *o@@@ @@    @@
#-------------------------------------------------------------------------------
# \author zhengrr
# \date 2016-8-1 ~ 3
# \copyright The MIT License
#-------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.0)
project("LangCPP"  VERSION 0.0.0.0  LANGUAGES CXX)

# Some local variables in project
set(pnom ${PROJECT_NAME})              # project name
string(TOUPPER ${PROJECT_NAME} pupr)   # project name upper
string(TOLOWER ${PROJECT_NAME} plwr)   # project name lower
set(psrc ${PROJECT_SOURCE_DIR})        # project source dir
set(pbin ${PROJECT_BINARY_DIR})        # project binary dir
set(pver ${PROJECT_VERSION})           # project version
set(pvermjr ${PROJECT_VERSION_MAJOR})  # project version major
set(pvermin ${PROJECT_VERSION_MINOR})  # project version minor
set(pverpch ${PROJECT_VERSION_PATCH})  # project version patch
set(pvertwk ${PROJECT_VERSION_TWEAK})  # project version tweak

if(WIN32)
   add_definitions("-DUNICODE" "-D_UNICODE")
endif()

add_subdirectory("src")
add_subdirectory("test")
add_subdirectory("doxygen")
