include(FetchContent)
FetchContent_Declare(
  gtest
  QUIET
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz)
# configure build of googletest
set(gtest_force_shared_crt
    ON
    CACHE BOOL "" FORCE)
set(BUILD_GMOCK
    OFF
    CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(gtest)

# file(READ resources/4.txt FILE_4_CONTENT) configure_file(ch_4_test.in.cpp
# ch_4_test.cpp @ONLY)
#
# file(READ resources/6.txt FILE_6_CONTENT) configure_file(ch_6_test.in.cpp
# ch_6_test.cpp @ONLY)
#

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(unit_tests common_test.cpp ch_1_test.cpp)

target_link_libraries(unit_tests PRIVATE common ch_1 gtest_main)

# automatic discovery of unit tests
include(GoogleTest)
gtest_discover_tests(
  unit_tests
  PROPERTIES LABELS "unit" DISCOVERY_TIMEOUT # how long to wait (in seconds)
                                             # before crashing
             240)
