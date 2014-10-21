cmake_minimum_required(VERSION 2.8)

PROJECT(SimpleLineParser)

include_directories(include)
aux_source_directory(src SRC_LIST)
aux_source_directory(ut  UT_LIST)

INCLUDE(FindGTest)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(unit_test ${UT_LIST} ${SRC_LIST})
target_link_libraries(unit_test ${GTEST_BOTH_LIBRARIES} pthread)

INCLUDE(FindBoost)
find_package(Boost 1.36.0 REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(demo demo.cpp ${SRC_LIST})