FILE(GLOB SOURCES
  "scripttag.h"
  "scripttag.cpp"
)

target_sources(ommpfritt PRIVATE ${SOURCES})

install(FILES scripttag.h
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ommpfritt/tags)
