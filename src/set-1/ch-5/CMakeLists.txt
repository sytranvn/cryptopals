add_library(ch_5)

target_sources(ch_5
  PRIVATE
    ch_5.cpp
  PUBLIC
    ch_5.h
  )

target_include_directories(ch_5
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )

target_link_libraries(ch_5
  PRIVATE
    common
    )
# we use this to get code coverage
# flags are only valid with the GNU compiler and on Linux
if(CMAKE_CXX_COMPILER_ID MATCHES GNU AND CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
  target_compile_options(ch_5
    PUBLIC
      "--coverage"
    )
  target_link_options(ch_5
    INTERFACE
      "--coverage"
    )
endif()
