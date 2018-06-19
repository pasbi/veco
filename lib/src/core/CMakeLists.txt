FILE(GLOB SOURCES
  "object.h"
  "object.cpp"
  "objectview.h"
  "objectview.cpp"
  "property.cpp"
  "property.h"
  "tag.cpp"
  "tag.h"
  "tagview.cpp"
  "tagview.h"
  "scene.cpp"
  "scene.h"
  "hasproperties.cpp"
  "hasproperties.h"
  "python.cpp"
  "python.h"
  "view.cpp"
  "view.h"
)

target_sources(ommpfritt PRIVATE ${SOURCES})

install(FILES object.h
              property.h
              tag.h
              properties.h
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ommpfritt/common)
