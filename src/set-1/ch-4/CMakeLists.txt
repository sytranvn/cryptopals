add_library(ch_4)

target_sources(ch_4
  PRIVATE
    ch_4.cpp
  PUBLIC
    ch_4.h
  )

target_include_directories(ch_4
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )

target_link_libraries(ch_4
  PRIVATE
    common
    ch_3
    )
# we use this to get code coverage
# flags are only valid with the GNU compiler and on Linux
if(CMAKE_CXX_COMPILER_ID MATCHES GNU AND CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
  target_compile_options(ch_4
    PUBLIC
      "--coverage"
    )
  target_link_options(ch_4
    INTERFACE
      "--coverage"
    )
endif()
