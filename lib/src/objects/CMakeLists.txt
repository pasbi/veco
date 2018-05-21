FILE(GLOB SOURCES
)

target_sources(ommpfritt PRIVATE ${SOURCES})

install(FILES 
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ommpfritt/tags)
