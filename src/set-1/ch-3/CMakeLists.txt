add_library(ch_3)

target_sources(ch_3
  PRIVATE
    ch_3.cpp
  PUBLIC
    ch_3.h
  )

target_include_directories(ch_3
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )

target_link_libraries(ch_3
  PRIVATE
    common
    )
# we use this to get code coverage
# flags are only valid with the GNU compiler and on Linux
if(CMAKE_CXX_COMPILER_ID MATCHES GNU AND CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
  target_compile_options(ch_3
    PUBLIC
      "--coverage"
    )
  target_link_options(ch_3
    INTERFACE
      "--coverage"
    )
endif()
