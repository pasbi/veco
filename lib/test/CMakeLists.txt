# Set Test data folder
set(TEST_DATA_DIR "${CMAKE_CURRENT_SOURCE_DIR}/data" CACHE FILEPATH "Path to the Test Data folder")
set(TEST_RESULT_DIR "${CMAKE_BINARY_DIR}/test_results" CACHE FILEPATH "Path to the Test Result folder")

add_definitions(-DTEST_DATA_DIR="${TEST_DATA_DIR}/")
add_definitions(-DTEST_RESULT_DIR="${TEST_RESULT_DIR}/")

file(MAKE_DIRECTORY ${TEST_RESULT_DIR})

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
include_directories("${CMAKE_SOURCE_DIR}/src")
include_directories("${CMAKE_BINARY_DIR}/src")

add_subdirectory(unit)
