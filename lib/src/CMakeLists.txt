add_library(ommpfritt "ommpfritt.h")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/config.cmake.h" "${CMAKE_CURRENT_BINARY_DIR}/config.h" @ONLY)

target_include_directories(ommpfritt PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_BINARY_DIR}")

install(TARGETS ommpfritt EXPORT OmmpfrittTargets
        PUBLIC_HEADER DESTINATION include/ommpfritt
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# install some header files for public usage. more are added in the sub directories
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/config.h
              ommpfritt.h
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ommpfritt)

set_target_properties(ommpfritt PROPERTIES VERSION ${OMMPFRITT_MAJOR_VERSION})
set_target_properties(ommpfritt PROPERTIES SOVERSION ${OMMPFRITT_VERSION})

add_definitions(-D_USE_MATH_DEFINES)

target_link_libraries(ommpfritt glog::glog)

find_package(Armadillo REQUIRED)
target_include_directories(ommpfritt PRIVATE ${ARMADILLO_INCLUDE_DIRS})
target_link_libraries(ommpfritt ${ARMADILLO_LIBRARIES})

find_package(PythonLibs 3 REQUIRED)
target_include_directories(ommpfritt PRIVATE ${PYTHON_INCLUDE_DIRS})
target_link_libraries(ommpfritt python3.6m)

FIND_PACKAGE(pybind11 REQUIRED)
target_link_libraries(ommpfritt pybind11::embed)

add_subdirectory(external)
add_subdirectory(core)
add_subdirectory(objects)
add_subdirectory(tags)
