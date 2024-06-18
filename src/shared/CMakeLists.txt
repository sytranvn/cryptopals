add_library(common)

file(GLOB SOURCES *.c)
file(GLOB HEADERS *.h)
target_sources(
  common
  PRIVATE ${SOURCES}
  PUBLIC ${HEADERS})

target_include_directories(common PUBLIC ${CMAKE_CURRENT_LIST_DIR})
