add_library(ch_6)

target_sources(ch_6
  PRIVATE
    ch_6.cpp
  PUBLIC
    ch_6.h
  )

target_include_directories(ch_6
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )

target_link_libraries(ch_6
  PRIVATE
    common
    )
# we use this to get code coverage
# flags are only valid with the GNU compiler and on Linux
if(CMAKE_CXX_COMPILER_ID MATCHES GNU AND CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
  target_compile_options(ch_6
    PUBLIC
      "--coverage"
    )
  target_link_options(ch_6
    INTERFACE
      "--coverage"
    )
endif()
