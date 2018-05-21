FILE(GLOB SOURCES
  "object.h"
  "object.cpp"
  "property.cpp"
  "property.h"
  "tag.cpp"
  "tag.h"
  "scene.cpp"
  "scene.h"
  "hasproperties.cpp"
  "hasproperties.h"
  "python.cpp"
  "python.h"
)

target_sources(ommpfritt PRIVATE ${SOURCES})

install(FILES object.h
              property.h
              tag.h
              properties.h
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ommpfritt/common)
