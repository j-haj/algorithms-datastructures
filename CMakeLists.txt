cmake_minimum_required(VERSION 3.0.2)
project(AlgorithmsDatastructures)

set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set(TEST_DIR "${PROJECT_SOURCE_DIR}/test")

set(CMAKE_CXX_STANDARD 14)

# Look for Google Test library
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Include headers
include_directories("${PROJECT_SOURCE_DIR}/src")

set(SOURCES
          ${SRC_DIR}/tools/tools.cc)

set(HEADERS
          ${SRC_DIR}/containers/vector.h
          ${SRC_DIR}/tools/tools.h)

set(TEST_HEADERS
          ${TEST_DIR}/containers/vector_test.h)

message("SOURCES: ${SOURCES}\n")
add_executable(test_runner ${TEST_DIR}/test_driver.cc ${SOURCES}
          ${HEADERS} ${TEST_HEADERS})

target_link_libraries(test_runner ${GTEST_BOTH_LIBRARIES})
