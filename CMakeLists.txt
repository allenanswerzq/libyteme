cmake_minimum_required(VERSION 3.5)

project(byte CXX)
set(CMAKE_CXX_STANDARD 11)

# Show detailed make command that runs
# set(CMAKE_VERBOSE_MAKEFILE ON)

# Print stuff
# include(CMakePrintHelpers)
# cmake_print_variables(MY_VARIABLE)
# cmake_print_properties(
#   TARGETS my_target
#   PROPERTIES POSITION_INDEPENDENT_CODE
# )

# Nice debug command
# cmake -S . -B build --trace-source=CMakeLists.txt --trace-expand -Wno-dev

# Switch debug or release build
# -DCMAKE_BUILD_TYPE=Debug

list(APPEND CMAKE_MODULE_PATH
  ${CMAKE_CURRENT_LIST_DIR}/CMake
  ${CMAKE_CURRENT_LIST_DIR}/CMake/copts
)

# include(AbseilInstallDirs)
include(CMakePackageConfigHelpers)
include(BytemeHelper)

# include current path
list(APPEND BYTE_COMMON_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

option(BYTE_RUN_TESTS "If ON, tests will be run." ON)
option(BYTE_USE_GOOGLETEST "If ON, use google test." ON)

# cmake_print_variables(${BYTE_RUN_TESTS})
# cmake_print_variables(${BYTE_USE_GOOGLETEST})

if(${BYTE_RUN_TESTS})
  # enable CTest.  This will set BUILD_TESTING to ON unless otherwise specified
  # on the command line
  include(CTest)
  enable_testing()
endif()

## check targets
if(BUILD_TESTING)

  if(${BYTE_USE_GOOGLETEST})
    include(CMake/Googletest/DownloadGTest.cmake)
    set(byte_gtest_src_dir ${CMAKE_BINARY_DIR}/googletest-src)
    set(byte_gtest_build_dir ${CMAKE_BINARY_DIR}/googletest-build)
  endif()

  check_target(gtest)
  check_target(gtest_main)
  check_target(gmock)

  list(APPEND BYTE_TEST_COMMON_LIBRARIES
    gtest_main
    gtest
    gmock
    ${CMAKE_THREAD_LIBS_INIT}
)
endif()

add_subdirectory(src)
