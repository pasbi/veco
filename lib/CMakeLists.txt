cmake_minimum_required(VERSION 3.1)

set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

project(ommpfritt CXX)

set(OMMPFRITT_MAJOR_VERSION 0)
set(OMMPFRITT_MINOR_VERSION 1)
set(OMMPFRITT_PATCH_VERSION 0)
set(OMMPFRITT_VERSION ${OMMPFRITT_MAJOR_VERSION}.${OMMPFRITT_MINOR_VERSION}.${OMMPFRITT_PATCH_VERSION})

# compile options
option(BUILD_TESTS "Build the tests" ON)
option(USE_OPENMP "Use OpenMP threading support." ON)
option(USE_OPENCL "Use OpenCL." ON)


# disable compilation inside the source tree. the results are harder to clean up and make it easy to commit build results
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
  message(FATAL_ERROR "In-source builds are not permitted. Make a separate folder for building:\nmkdir build; cd build; cmake ..\nBefore that, remove the files already created:\nrm -rf CMakeCache.txt CMakeFiles")
endif(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)

# when no install target is set, default to install/ in the build dir
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  message(STATUS "No install prefix set, defaulting to ${CMAKE_BINARY_DIR}/install")
  set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH "default install path" FORCE )
endif()

# Set available configurations
set(CMAKE_CONFIGURATION_TYPES "Debug;Release;" CACHE STRING "" FORCE)

# Support folders in project
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "_")

# FLAGS
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")


# enable debug symbols on Linux
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O3")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O3 -Wall")
endif()

# Tell CMake where to look for modules
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/Modules/" ${CMAKE_MODULE_PATH})
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/" ${CMAKE_MODULE_PATH})


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# checks for dependencies
find_package(OpenCV 3.0 REQUIRED)

find_package (glog 0.3.5 REQUIRED)

if(USE_OPENMP)
  find_package(OpenMP)
  if(OpenMP_C_FLAGS)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
  endif()

  if(OpenMP_CXX_FLAGS)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
  endif()

  if(WIN32)
    list(APPEND LIBS gomp)
  endif(WIN32)
endif(USE_OPENMP)

add_subdirectory(src)

if(BUILD_TESTS)
  add_subdirectory(test)
endif()


export(TARGETS ommpfritt FILE OmmpfrittTargets.cmake)

export(PACKAGE ommpfritt)

configure_package_config_file(OmmpfrittConfig.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/OmmpfrittConfig.cmake
                              INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Ommpfritt
                              PATH_VARS CMAKE_INSTALL_LIBDIR CMAKE_INSTALL_INCLUDEDIR
                              NO_CHECK_REQUIRED_COMPONENTS_MACRO)

write_basic_package_version_file(OmmpfrittConfigVersion.cmake VERSION ${OMMPFRITT_VERSION} COMPATIBILITY SameMajorVersion)

install(EXPORT OmmpfrittTargets FILE OmmpfrittTargets.cmake DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Ommpfritt)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/OmmpfrittConfig.cmake ${CMAKE_CURRENT_BINARY_DIR}/OmmpfrittConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Ommpfritt )
