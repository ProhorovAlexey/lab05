cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_FLAGS "-fprofile-arcs -ftest-coverage")

project(banking)

set(LIBS banking/Transaction.cpp banking/Account.cpp)

add_library(${PROJECT_NAME} ${LIBS})

include_directories(${PROJECT_NAME} include)

option(BUILD_TESTS "Builds tests" ON)

if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(third-party/gtest)
  add_executable(tests tests/test.cpp)
  target_link_libraries(tests ${PROJECT_NAME} gtest_main)
  add_test(NAME unit_test COMMAND tests)
endif()
