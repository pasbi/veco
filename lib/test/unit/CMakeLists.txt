# Add source files
FILE(GLOB SRC_FILES
  "common.cpp"
  "common.h"
  "test_object.cpp"
  "test_tag.cpp"
  "test_scripttag.cpp"
)

# Add executable
add_executable(ommpfritt_unit_tests ${SRC_FILES})

target_link_libraries(ommpfritt_unit_tests ommpfritt)

# Link gtest
target_link_libraries(ommpfritt_unit_tests gtest)
target_link_libraries(ommpfritt_unit_tests gtest_main)
include_directories(${gtest_SOURCE_DIR}/include)

find_package(PythonLibs 3 REQUIRED)
target_include_directories(ommpfritt_unit_tests PRIVATE ${PYTHON_INCLUDE_DIRS})
#target_link_libraries(ommpfritt_unit_tests python3.6m)

# Set folder name
set_target_properties(ommpfritt_unit_tests PROPERTIES FOLDER "tests")
