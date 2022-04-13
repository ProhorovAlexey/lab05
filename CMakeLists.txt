cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(banking)

set(LIBS ${CMAKE_CURRENT_SOURCE_DIR}/banking/Transaction.cpp ${CMAKE_CURRENT_SOURCE_DIR}/banking/Account.cpp)

add_library(${PROJECT_NAME} ${LIBS})

include_directories(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/include)

option(BUILD_TESTS "Builds tests" ON)

if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/third-party/gtest)
  add_executable(tests ${CMAKE_CURRENT_SOURCE_DIR}/tests/test.cpp)
  target_link_libraries(tests ${PROJECT_NAME} gtest_main)
  add_test(NAME unit_test COMMAND tests)
endif()
