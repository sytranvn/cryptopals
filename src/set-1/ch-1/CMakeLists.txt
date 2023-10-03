add_library(ch_1)

target_sources(ch_1
  PRIVATE
    ch_1.cpp
  PUBLIC
    ch_1.h
  )

target_include_directories(ch_1
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )

target_link_libraries(ch_1
  PRIVATE
    common
    )
# we use this to get code coverage
# flags are only valid with the GNU compiler and on Linux
if(CMAKE_CXX_COMPILER_ID MATCHES GNU AND CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
  target_compile_options(ch_1
    PUBLIC
      "--coverage"
    )
  target_link_options(ch_1
    INTERFACE
      "--coverage"
    )
endif()
